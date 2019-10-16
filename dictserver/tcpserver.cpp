#include "tcpserver.h"
#include "tcpsocket.h"


TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{

}
void TcpServer::incomingConnection(qintptr id)
{
    TcpSocket *tcpSocket=new TcpSocket(this);
    tcpSocket->setSocketDescriptor(id);
}
