#include "dictdialog.h"
#include "ui_dictdialog.h"
#include <QtWidgets>

DictDialog::DictDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DictDialog)
{
    ui->setupUi(this);
    QIcon icon;
    icon.addFile(tr(":/images/find.png"));
    ui->pushButton->setIcon(icon);

    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(sendRequest()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readResponse()));
}

DictDialog::~DictDialog()
{
    delete ui;
}

void DictDialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"error","请输入单词");
        return;
    }
    nextBlockSize=0;
    tcpSocket->connectToHost("127.0.0.1",7788);
}

void DictDialog::sendRequest()
{
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out << quint16(0);
    out << quint8('Q') << ui->lineEdit->text();
    out.device()->seek(0);
    out << quint16(buf.size()-sizeof(quint16));
    tcpSocket->write(buf);
}

void DictDialog::readResponse()
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
    in >> type;
    if(type==quint8('Q'))
    {
        QString str;
        in >> str;
        ui->textBrowser->setText(str);
    }
    tcpSocket->close();
}
