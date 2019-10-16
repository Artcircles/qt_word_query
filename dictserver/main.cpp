#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer tcpServer;
    tcpServer.listen(QHostAddress::Any,7788);

    QPushButton pushButton("quit");
    pushButton.setGeometry(100,100,200,200); //前两个参数是位置坐标，后两个参数是按钮的尺寸。
    pushButton.show();

    QObject::connect(&pushButton,SIGNAL(clicked()),&a,SLOT(quit()));

    return a.exec();
}
