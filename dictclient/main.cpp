#include "logindialog.h"
#include "dictdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog w;
    if(w.exec()==QDialog::Rejected)
        return 0;
    DictDialog d;
    d.show();

    return a.exec();
}
