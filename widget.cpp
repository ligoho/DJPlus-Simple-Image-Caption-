#include "widget.h"
#include "ui_widget.h"

#include <qsettings.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->LinkButton->setFlat(true);
    ui->sendText->setReadOnly(true);
    ui->receiveText->setReadOnly(true);
    ui->label_3->setVisible(false);

    ui->IPlineEdit->setPlaceholderText("xxx.xxx.xxx.xxx");
    ui->PortlineEdit->setPlaceholderText("1 - 65525");
    ui->command->setPlaceholderText("Enter some commands...");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_LinkButton_clicked()
{
//    QSettings wallPaper("HKEY_CURRENT_USER\\Control Panel\\Desktop",
//                           QSettings::NativeFormat);

//        //新的桌面图片路径
//        QString path("C:/Users/ligoh/Pictures/Camera Roll/WIN_20220201_19_51_22_Pro.jpg");

//        //给壁纸注册表设置新的值（新的图片路径）
//        wallPaper.setValue("Wallpaper",path);
//        QByteArray byte = path.toLocal8Bit();

//        //调用windowsAPI
//        SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, byte.data(), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);

//    GetSystemTime(&time);
//    qDebug()<< time.wHour + 8 << ":" << time.wMinute <<time.wSecond;

    m_ip = ui->IPlineEdit->text();
    m_port = ui->PortlineEdit->text();

    if(m_ip.isEmpty()&&m_port.isEmpty())
    {
        ui->label_3->setText("Wrong IP or Port!");
        ui->label_3->setStyleSheet("#label_3{color:red}");
        ui->label_3->setVisible(true);
        return;
    }
    qDebug()<<"ok, fine.";

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
        iResutlt = ::connect(m_socket, (sockaddr*)&m_addr, sizeof(struct sockaddr_in));

        if(iResutlt == SOCKET_ERROR)
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
        }

    }


}

