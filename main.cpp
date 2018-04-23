#include "NetUtils.h"
#include "http/SendDataHttp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yang::NetUtils w;
    w.show();

    return a.exec();
}
