#include "stdafx.h"
#include "mainwindow.h"
#include "camerafeed.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    VideoCapture = new CameraFeed(this);

    connect(VideoCapture, &CameraFeed::newPixmapCaptured, this, [&]() {
        ui.cam1->setPixmap(VideoCapture->pixmap().scaled(640, 480));
        });
}

void MainWindow::on_StartCameras_button_clicked()
{
    VideoCapture->start(QThread::HighPriority);
}

MainWindow::~MainWindow()
{
    VideoCapture->terminate();
}
