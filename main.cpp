#include "NetUtils.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetUtils w;
    w.show();

    return a.exec();
}
