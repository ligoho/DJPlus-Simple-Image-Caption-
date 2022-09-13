#ifndef M_CONNECTION_H
#define M_CONNECTION_H

//#include "windows.h"
#include <WinSock2.h>
#include <QDebug>
#include <QObject>
#include <QTimer>

#define buf_len 100000

class m_connection : public QObject
{
    Q_OBJECT
public:
    explicit m_connection(QObject *parent = nullptr, const SOCKET& sock = NULL);

signals:
    void _disconnect();
    void sendByteArray(QByteArray ba);

public slots:
    void check_Connection();
    void run();

private:
    SOCKET m_sock;
    char recvbuf[buf_len];
    int iResult = 0;
    int iSendResult = 0;

    QTimer* timer;

};

#endif // M_CONNECTION_H
