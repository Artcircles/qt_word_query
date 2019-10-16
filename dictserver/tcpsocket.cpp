#include "tcpsocket.h"


TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent)
{
    nextBlockSize=0;
    connect(this,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open())
        QMessageBox::warning(nullptr,"Error","Open database failed!!!");
}

void TcpSocket::readClient()
{
    QDataStream in(this);
    if(nextBlockSize==0)
    {
        if(bytesAvailable() < sizeof(quint16))
            return;
        in >> nextBlockSize;
    }
    if(bytesAvailable() < nextBlockSize)
        return;
    quint8 type;
    in >> type;
    QString username,password,word;
    if(type==quint8('L'))
    {
        // 登录
        in >> username >> password;
        if(username.isEmpty() || password.isEmpty())
        {
            QMessageBox::warning(nullptr,"Error","无用户名或密码！！！");
            return;
        }
        else
        {
            QString str=QString("select * from login where username = '%1' and password = '%2' ").arg(username).arg(password);
            QSqlQuery query;
            query.exec(str);
            if(query.first())
            {
                //QMessageBox::information(nullptr,"success","登录成功！！！");
                nextBlockSize = 0;
                QByteArray buf;
                QDataStream out(&buf,QIODevice::WriteOnly);
                out << quint16(0);
                out << type << QString("success");
                out.device()->seek(0);
                out << quint16(buf.size() - sizeof(quint16));
                write(buf);
            }
            else
                QMessageBox::warning(nullptr,"Error","用户名或密码错误！！！");
        }
    }
    else if(type==quint8('R'))
    {
        // 注册
        in >> username >> password;
        if(username.isEmpty() || password.isEmpty())
        {
            QMessageBox::warning(nullptr,"Error","无用户名或密码！！！");
            return;
        }
        else {
            QSqlQuery query;
            QString str = QString("insert into login values('%1',%2) ").arg(username).arg(password);
            QString str1 = QString("select * from login where username = '%1' ").arg(username);
            if (query.exec(str1) && query.first())
                QMessageBox::warning(nullptr,"Error","用户名重复");
            else if (query.exec(str))
            {
                QMessageBox::information(nullptr,"Success","注册成功！！！",QMessageBox::Yes);
                return;
            }
            else
                QMessageBox::warning(nullptr,"Error","注册失败，请重试！！！");
        }
    }
    else if(type==quint8('Q'))
    {
        in >> word;
        QFile file("dict.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(nullptr,"Error", "Open dict.txt error");
            return;
        }
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            if (line.startsWith(word + " "))
            {
                line = line.mid(word.length());
                line = line.trimmed();

                nextBlockSize = 0;
                QByteArray buf;
                QDataStream out(&buf,QIODevice::WriteOnly);
                out << quint16(0);
                out << type << QString(line);
                out.device()->seek(0);
                out << quint16(buf.size() - sizeof(quint16));
                write(buf);
                return;
            }
        }
        nextBlockSize = 0;
        QByteArray buf;
        QDataStream out(&buf,QIODevice::WriteOnly);
        out << quint16(0);
        out << type << QString("No found");
        out.device()->seek(0);
        out << quint16(buf.size() - sizeof(quint16));
        write(buf);
    }
    close();
}
