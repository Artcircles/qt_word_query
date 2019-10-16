#include "logindialog.h"
#include "ui_logindialog.h"
#include <QtWidgets>
#include <QHostAddress>

/*
 'L'  登录
 'R'  注册
 'Q'  单词
 */

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    QPixmap pix(":/images/username.png");
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    QPixmap pix1(":/images/password.png");
    int w1 = ui->label_2->width();
    int h1 = ui->label_2->height();
    ui->label_2->setPixmap(pix1.scaled(w1,h1,Qt::KeepAspectRatio));
    setWindowTitle("Sigin");

    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(sendRequest()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readResponse()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"ERROR","无用户名或密码");
        return;
    }
    nextBlockSize=0;
    tcpSocket->connectToHost(QHostAddress("127.0.0.1"),7788);
}

void LoginDialog::sendRequest()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();

    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out << quint16(0);
    if(ui->radioButton->isChecked())
        out << quint8('L');
    else
        out << quint8('R');
    out << username << password;
    out.device()->seek(0);
    out << quint16(buf.size()-sizeof(quint16));
    tcpSocket->write(buf);
}

void LoginDialog::readResponse()
{
    QDataStream in(tcpSocket);
    if(nextBlockSize==0)
    {
        if(tcpSocket->bytesAvailable() < sizeof(quint16))
            return;
        in >> nextBlockSize;
    }
    if(tcpSocket->bytesAvailable() < nextBlockSize)
        return;
    quint8 type;
    QString str;
    in >> type >> str;
    tcpSocket->close();
    if(type==quint8('L') && str=="success")
    {
        accept();
        return;
    }
    if(type==quint8('L'))
    {
        QMessageBox::information(this,"error","login error");
    }
    else
    {
        QMessageBox::information(this,"register",str);
    }

}
