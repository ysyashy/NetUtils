#include "NetUtils.h"
//#include "http/SendDataHttp.h"
#include <QApplication>
#include <QDataStream>
#include <parse/ParseData.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yang::NetUtils w;
    w.show();
    w.show();

    return a.exec();
}
