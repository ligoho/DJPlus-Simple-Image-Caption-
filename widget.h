#ifndef WIDGET_H
#define WIDGET_H

#include "windows.h"
#include <WinSock2.h>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_LinkButton_clicked();

private:
    Ui::Widget *ui;

    SYSTEMTIME time; //windowsAPI时间结构体
    sockaddr_in m_addr; //连接地址结构体
    SOCKET m_socket;  //socket结构体
    QString m_ip;
    QString m_port;

    int iResutlt = 0;

};
#endif // WIDGET_H
