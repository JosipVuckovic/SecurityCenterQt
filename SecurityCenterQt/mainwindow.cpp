#include "stdafx.h"
#include "mainwindow.h"
#include "camerafeed.h"
#include "settingswindow.h"


MainWindow::MainWindow(QWidget* parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
		
	//TODO: There has to be a better way...
	
	CameraSettingsResult* Cam1 = loadSettingsFromRegistry(CAM1);
	if (Cam1 != nullptr)
	{
		if (Cam1->direcltyConnected != nullptr)
		{
			VideoCapture_Cam1 = new CameraFeed(*Cam1->direcltyConnected, this);
		}
		else if (Cam1->ipcamera != nullptr)
		{
			VideoCapture_Cam1 = new CameraFeed(*Cam1->ipcamera, this);
		}
	}
	else
	{
		VideoCapture_Cam1 = nullptr;
	}
	
	CameraSettingsResult* Cam2 = loadSettingsFromRegistry(CAM2);
	if (Cam2 != nullptr)
	{
		if (Cam2->direcltyConnected != nullptr)
		{
			VideoCapture_Cam2 = new CameraFeed(*Cam2->direcltyConnected, this);
		}
		else if (Cam2->ipcamera != nullptr)
		{
			VideoCapture_Cam2 = new CameraFeed(*Cam2->ipcamera, this);
		}
	}
	else
	{
		VideoCapture_Cam2 = nullptr;
	}

	CameraSettingsResult* Cam3 = loadSettingsFromRegistry(CAM3);
	if (Cam3 != nullptr)
	{
		if (Cam3->direcltyConnected != nullptr)
		{
			VideoCapture_Cam3 = new CameraFeed(*Cam3->direcltyConnected, this);
		}
		else if (Cam3->ipcamera != nullptr)
		{
			VideoCapture_Cam3 = new CameraFeed(*Cam3->ipcamera, this);
		}
	}
	else
	{
		VideoCapture_Cam3 = nullptr;
	}

	
	
	

	//TODO: Read W/H from app settings	
	//TODO: PROP:  On double click on one, have it in full screen? Y/N
		
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
	//CRY!!!!
	if (VideoCapture_Cam1 != nullptr)
	{
		VideoCapture_Cam1->start();
	}
	else
	{
		ui.cam1_record_button->setDisabled(true);
		ui.cam1_take_shot_button->setDisabled(true);
		ui.cam1->setPixmap(QPixmap::fromImage(QImage(":/MainWindow/noCamera.jpg")));
	}

	if (VideoCapture_Cam2 != nullptr)
	{
		VideoCapture_Cam2->start();
	}
	else
	{
		ui.cam2->setPixmap(QPixmap::fromImage(QImage(":/MainWindow/noCamera.jpg")));
	}

	if (VideoCapture_Cam3 != nullptr)
	{
		VideoCapture_Cam3->start();
	}	
	else
	{
		ui.cam3->setPixmap(QPixmap::fromImage(QImage(":/MainWindow/noCamera.jpg")));
	}
}

MainWindow::~MainWindow()
{
	if (VideoCapture_Cam1 != nullptr)
	{
		VideoCapture_Cam1->terminate();
	}
	if (VideoCapture_Cam2 != nullptr)
	{
		VideoCapture_Cam2->terminate();
	}
	if (VideoCapture_Cam3 != nullptr)
	{
		VideoCapture_Cam3->terminate();
	}
}

void MainWindow::on_cam1_take_shot_button_clicked()
{
	if (VideoCapture_Cam1->saveCameraScreenshot())
	{
		QMessageBox::NoIcon(this, "Info", "Image saved", "OK");
	}
	else
	{
		QMessageBox::critical(this, "Error", "Failed to save image", "OK");
	}
}

//TODO: In ideal world, this would be signals...
void MainWindow::on_cam1_record_button_clicked()
{	
	if (!recording)
	{
		recording = true;
		VideoCapture_Cam1->initRecording(recording);			
	}
	else
	{
		recording = false;		
		VideoCapture_Cam1->releaseRecording(recording);
	}	
}

void MainWindow::on_settings_button_clicked()
{	
	SettingsWindow setttingsWindow(this);
	setttingsWindow.exec();	
}
