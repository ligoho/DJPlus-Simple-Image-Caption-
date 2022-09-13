#include "m_connection.h"

m_connection::m_connection(QObject *parent, const SOCKET& sock)
    : QObject{parent}, m_sock{sock}
{
}

void m_connection::run()
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&m_connection::check_Connection);
    timer->start(500);
}
void m_connection::check_Connection()
{
    iResult = recv(m_sock, recvbuf, buf_len, 0);

        if (iResult > 0)
        {
            qDebug()<< "Bytes received: " + QString::number(iResult);
            emit sendByteArray(QByteArray(recvbuf));
        }
        else if (iResult == 0)
        {
            qDebug()<< "断开连接";
            timer->stop();
            delete timer;

            emit _disconnect();
        }
        else
        {
            qDebug() << "recv failed: %d\n";
        }
}

