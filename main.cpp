#include "MainWindow.h"

#include <QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain("org.helper.darknet.www");
    a.setOrganizationName("yujinghuanqiu");
    a.setApplicationName("DarknetHelper");

    MainWindow w;
    w.show();
    return a.exec();
}
