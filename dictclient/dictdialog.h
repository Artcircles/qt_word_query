#ifndef DICTDIALOG_H
#define DICTDIALOG_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class DictDialog;
}

class DictDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DictDialog(QWidget *parent = nullptr);
    ~DictDialog();

private slots:
    void on_pushButton_clicked();
    void sendRequest();
    void readResponse();

private:
    Ui::DictDialog *ui;
    QTcpSocket *tcpSocket;
    quint16 nextBlockSize;
};

#endif // DICTDIALOG_H
