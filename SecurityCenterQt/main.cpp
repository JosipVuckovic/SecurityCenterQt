#include "stdafx.h"
#include "mainwindow.h"
#include "globalstrings.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QCoreApplication::setOrganizationName(SCStrings::_myName);
    QCoreApplication::setApplicationName(SCStrings::_nwp);

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
