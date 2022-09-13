#ifndef WIDGET_H
#define WIDGET_H

//#include "windows.h"
#include "m_connection.h"
#include "m_label.h"
#include <WinSock2.h>
#include <QWidget>
#include <QMessageBox>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void _run();
    void _draw();
    void _clear();

public slots:
    void on_LinkButton_clicked();
    void disconnection();
    void byteArrayProcess(QByteArray ba);

private slots:
    void on_pushButton_clicked();
    void on_draw_clicked();
    void on_clear_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;

    SYSTEMTIME time; //windowsAPI时间结构体
    sockaddr_in m_addr; //连接地址结构体
    SOCKET m_socket;  //socket结构体
    QString m_ip;
    QString m_port;
    QTimer* timer;
    QThread* m_thread;
    m_connection* check;

    int iResult = 0;
    int iSendResult = 0;

};
#endif // WIDGET_H
