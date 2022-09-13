#include "widget.h"
#include "ui_widget.h"

#include <QFile>
//#include <qsettings.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    ui->LinkButton->setFlat(true);
    ui->sendText->setReadOnly(true);
    ui->receiveText->setReadOnly(true);
    ui->label_3->setVisible(false);

    ui->IPlineEdit->setPlaceholderText("xxx.xxx.xxx.xxx");
    ui->PortlineEdit->setPlaceholderText("1 - 65525");
    ui->command->setPlaceholderText("Enter some commands...");
    ui->img_2->setPixmap(QPixmap(":/pic/res/img.png"));
}

Widget::~Widget()
{
    delete ui;
}

/*以tcp-server的方式连接*/
void Widget::on_LinkButton_clicked()
{

    m_ip = ui->IPlineEdit->text();
    m_port = ui->PortlineEdit->text();

    if(m_ip.isEmpty()&&m_port.isEmpty())
    {
        ui->label_3->setText("Wrong IP or Port!");
        ui->label_3->setStyleSheet("#label_3{color:red}");
        ui->label_3->setVisible(true);
        return;
    }

    ui->label_3->setText("Connect...");
    ui->label_3->setStyleSheet("#label_3{color:blue}");
    ui->label_3->setVisible(true);

    /*winsocket连接*/

    //初始化网络环境
    WSADATA Data;
    //定义socket的版本号
    WORD Version = MAKEWORD(2, 2);
    //配置版本
    int isInitSuccessed = ::WSAStartup(Version, &Data);

    if(isInitSuccessed)
    {
        //初始化网络环境失败
        QMessageBox::information(NULL,"WARNING","Socket environment initialization failed !");
    }
    else
    {
        //初始化网络环境成功

        //创建socket
        m_socket = ::socket(AF_INET, SOCK_STREAM, 0); //设置流式嵌套字

        m_addr.sin_family = AF_INET; //设置ipv4协议

        m_addr.sin_addr.s_addr = ::inet_addr(m_ip.toLatin1()); //设置ip
        m_addr.sin_port = ::htons(m_port.toUShort()); //设置port

        //与服务器连接
        iResult = ::connect(m_socket, (sockaddr*)&m_addr, sizeof(struct sockaddr_in));

        if(iResult == SOCKET_ERROR)
        {
            ui->label_3->setText("Connection Failed !");
            ui->label_3->setStyleSheet("#label_3{color:red}");
            ui->label_3->setVisible(true);
            return;
        }
        else
        {
            ui->label_3->setText("Connected.");
            ui->label_3->setStyleSheet("#label_3{color:green}");
            ui->label_3->setVisible(true);
            ui->LinkButton->setEnabled(false);

            m_thread = new QThread;
            check = new m_connection(nullptr, m_socket);

            connect(check,&m_connection::_disconnect,this,&Widget::disconnection);
            connect(this,&Widget::_run,check,&m_connection::run);
            connect(check,&m_connection::sendByteArray,this,&Widget::byteArrayProcess);

            check->moveToThread(m_thread);
//            check->run();

            emit _run();

            //启动线程
            m_thread->start();
        }
    }
}

void Widget::disconnection()
{
    ui->LinkButton->setEnabled(true);
    ui->label_3->setText("Disconnected !");
    ui->label_3->setStyleSheet("#label_3{color:red}");
    ui->label_3->setVisible(true);

    m_thread->exit();
    delete check;
    m_thread->deleteLater();
}

/*处理接收字节*/
void Widget::byteArrayProcess(QByteArray ba)
{
    QString ss = QString::fromLatin1(ba.data(), ba.size());

    QByteArray rc = QByteArray::fromHex(ss.toLatin1());
    QByteArray rdc = qUncompress(rc); //解压

    QImage img;
    img.loadFromData(rdc);

    ui->img_2->setPixmap(QPixmap::fromImage(img));
    ui->img_2->resize(img.width(),img.height());
    ui->img->resize(img.width(),img.height());
    ui->receiveText->append(ss);
    qDebug()<<ui->img_2->width()<<ui->img->width()<<ui->img->height();
}

/*发送命令*/
void Widget::on_pushButton_clicked()
{
    char* c = ui->command->toPlainText().toLatin1().data();
    iSendResult = send(m_socket, c, (int)strlen(c), 0);

    ui->sendText->append(ui->command->toPlainText());
    if(iSendResult != SOCKET_ERROR)
    {
        ui->command->clear();
        ui->sendText->append("Send successfully!");
    }
    else
    {
        ui->sendText->append("Error occurred when sending the command!");

    }
}

