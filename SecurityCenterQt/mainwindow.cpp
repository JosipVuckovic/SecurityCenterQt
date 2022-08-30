#include "stdafx.h"
#include "mainwindow.h"
#include "camerafeed.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//TODO: Implement Settings
	//TODO: Read camera connection data from settings
	//TODO: PROP: Just create more video captures or use some sort of worer??

	VideoCapture_Cam1 = new CameraFeed(HARDCODED_CAMERAID, this);
	VideoCapture_Cam2 = new CameraFeed(HARDCODED_IP_CAMERA1, this);
	VideoCapture_Cam3 = new CameraFeed(HARDCODED_IP_CAMERA2, this);


	//TODO: Read W/H from settings
	//TODO: Have 4 cams or 2 Y/N
	//TODO: PROP:  On double click on one, have it in full screen? Y/N
	//TODO: PROP:  Have take screenshot of cam feed Y/N
	//TODO: PROP:  save cam feed to file Y/N

	connect(VideoCapture_Cam1, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam1->setPixmap(VideoCapture_Cam1->pixmap().scaled(640, 480));
		});

	connect(VideoCapture_Cam2, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam2->setPixmap(VideoCapture_Cam2->pixmap().scaled(640, 480));
		});

	connect(VideoCapture_Cam3, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam3->setPixmap(VideoCapture_Cam3->pixmap().scaled(640, 480));
		});
}

void MainWindow::on_StartCameras_button_clicked()
{
	VideoCapture_Cam1->start(QThread::HighPriority);
	VideoCapture_Cam2->start(QThread::HighestPriority);
	VideoCapture_Cam3->start(QThread::HighPriority);
}

MainWindow::~MainWindow()
{
	VideoCapture_Cam1->terminate();
	VideoCapture_Cam2->terminate();
	VideoCapture_Cam3->terminate();
}
