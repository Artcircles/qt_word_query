#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlQuery>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket(QObject *parent=nullptr);
private slots:
    void readClient();
private:
    quint16 nextBlockSize;
};

#endif // TCPSOCKET_H
