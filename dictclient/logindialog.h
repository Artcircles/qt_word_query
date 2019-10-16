#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_clicked();
    void sendRequest();
    void readResponse();

private:
    Ui::LoginDialog *ui;
    QTcpSocket *tcpSocket;
    quint16 nextBlockSize;
};

#endif // LOGINDIALOG_H
