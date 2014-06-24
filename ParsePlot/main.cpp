#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include <QVector>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Hyperion");
    a.setOrganizationDomain("hyperiontg.com");
    a.setApplicationName("ParsePlot");
    MainWindow w;
    w.show();

    return a.exec();
}
