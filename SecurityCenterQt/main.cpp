#include "stdafx.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QCoreApplication::setOrganizationName("JosipVuckovic");
    QCoreApplication::setApplicationName("NWP_SecurityCenterQt");

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
