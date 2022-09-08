#include "stdafx.h"
#include "mainwindow.h"
#include "globalstrings.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QCoreApplication::setOrganizationName(_myName);
    QCoreApplication::setApplicationName(_nwp);

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
