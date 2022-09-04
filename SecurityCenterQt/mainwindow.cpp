#include "stdafx.h"
#include "mainwindow.h"
#include "camerafeed.h"
#include "settingswindow.h"

MainWindow::MainWindow(QWidget* parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
			
	disableAllButtons();

	Camera Cam1 = loadSettingsFromRegistry(CAM1);
	Camera Cam2 = loadSettingsFromRegistry(CAM2);
	Camera Cam3 = loadSettingsFromRegistry(CAM3);
	Camera Cam4 = loadSettingsFromRegistry(CAM4);
	
	VideoCapture_Cam1 = new CameraFeed(Cam1, this);
	VideoCapture_Cam2 = new CameraFeed(Cam2, this);
	VideoCapture_Cam3 = new CameraFeed(Cam3, this);
	VideoCapture_Cam4 = new CameraFeed(Cam4, this);
	
	//TODO: Read W/H from app settings N:No time...
	//TODO: PROP:  On double click on one, have it in full screen? Y/N N
		
	connect(ui.cam1, SIGNAL(clicked()), this, SLOT(label1clicked()));

		
	connect(VideoCapture_Cam1, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam1->setPixmap(VideoCapture_Cam1->pixmap().scaled(640, 480));
		ui.cam1_record_button->setEnabled(VideoCapture_Cam1->isIsRecieving());
		ui.cam1_take_shot_button->setEnabled(VideoCapture_Cam1->isIsRecieving());
		});	

	connect(VideoCapture_Cam2, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam2->setPixmap(VideoCapture_Cam2->pixmap().scaled(640, 480));
		ui.cam2_record_button->setEnabled(VideoCapture_Cam2->isIsRecieving());
		ui.cam2_take_shot_button->setEnabled(VideoCapture_Cam2->isIsRecieving());
		});

	connect(VideoCapture_Cam3, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam3->setPixmap(VideoCapture_Cam3->pixmap().scaled(640, 480));
		ui.cam3_record_button->setEnabled(VideoCapture_Cam3->isIsRecieving());
		ui.cam3_take_shot_button->setEnabled(VideoCapture_Cam3->isIsRecieving());
		});

	connect(VideoCapture_Cam4, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam4->setPixmap(VideoCapture_Cam4->pixmap().scaled(640, 480));
		ui.cam4_record_button->setEnabled(VideoCapture_Cam4->isIsRecieving());
		ui.cam4_take_shot_button->setEnabled(VideoCapture_Cam4->isIsRecieving());
		});
}

void MainWindow::disableAllButtons()
{
	ui.cam1_record_button->setDisabled(true);
	ui.cam1_take_shot_button->setDisabled(true);
	ui.cam2_record_button->setDisabled(true);
	ui.cam2_take_shot_button->setDisabled(true);
	ui.cam3_record_button->setDisabled(true);
	ui.cam3_take_shot_button->setDisabled(true);
	ui.cam4_record_button->setDisabled(true);
	ui.cam4_take_shot_button->setDisabled(true);
}

void MainWindow::on_StartCameras_button_clicked()
{	
		VideoCapture_Cam1->start();
		VideoCapture_Cam2->start();
		VideoCapture_Cam3->start();
		VideoCapture_Cam4->start();
}

MainWindow::~MainWindow()
{
	VideoCapture_Cam1->terminate();
	delete VideoCapture_Cam1;

	VideoCapture_Cam2->terminate();
	delete VideoCapture_Cam2;

	VideoCapture_Cam3->terminate();
	delete VideoCapture_Cam3;

	VideoCapture_Cam4->terminate();
	delete VideoCapture_Cam4;
}

void MainWindow::on_cam1_take_shot_button_clicked()
{
	if (VideoCapture_Cam1->saveCameraScreenshot())
	{
		successTakeShot();
	}
	else
	{
		failedTakeShot();
	}
}

void MainWindow::on_cam2_take_shot_button_clicked()
{
	if (VideoCapture_Cam2->saveCameraScreenshot())
	{
		successTakeShot();
	}
	else
	{
		failedTakeShot();
	}
}

void MainWindow::on_cam3_take_shot_button_clicked()
{
	if (VideoCapture_Cam3->saveCameraScreenshot())
	{
		successTakeShot();
	}
	else
	{
		failedTakeShot();
	}
}

void MainWindow::on_cam4_take_shot_button_clicked()
{
	if (VideoCapture_Cam4->saveCameraScreenshot())
	{
		successTakeShot();
	}
	else
	{
		failedTakeShot();
	}
}


void MainWindow::on_cam1_record_button_clicked()
{	
	if (!recordingCam1)
	{
		recordingCam1 = true;
		VideoCapture_Cam1->initRecording(recordingCam1);
		ui.cam1_record_button->setText("Stop recording");
	}
	else
	{
		recordingCam1 = false;		
		VideoCapture_Cam1->releaseRecording(recordingCam1);
		ui.cam1_record_button->setText("Start recording");
	}	
}

void MainWindow::on_cam2_record_button_clicked()
{
	if (!recordingCam2)
	{
		recordingCam2 = true;
		VideoCapture_Cam2->initRecording(recordingCam2);
		ui.cam1_record_button->setText("Stop recording");
	}
	else
	{
		recordingCam2 = false;
		VideoCapture_Cam2->releaseRecording(recordingCam2);
		ui.cam2_record_button->setText("Start recording");
	}
}

void MainWindow::on_cam3_record_button_clicked()
{
	if (!recordingCam3)
	{
		recordingCam3 = true;
		VideoCapture_Cam3->initRecording(recordingCam3);
		ui.cam3_record_button->setText("Stop recording");
	}
	else
	{
		recordingCam3 = false;
		VideoCapture_Cam3->releaseRecording(recordingCam2);
		ui.cam3_record_button->setText("Start recording");
	}
}

void MainWindow::on_cam4_record_button_clicked()
{
	if (!recordingCam4)
	{
		recordingCam4 = true;
		VideoCapture_Cam4->initRecording(recordingCam4);
		ui.cam4_record_button->setText("Stop recording");
	}
	else
	{
		recordingCam4 = false;
		VideoCapture_Cam4->releaseRecording(recordingCam4);
		ui.cam4_record_button->setText("Start recording");
	}
}

void MainWindow::on_settings_button_clicked()
{	
	SettingsWindow setttingsWindow(this);
	setttingsWindow.exec();	
}

void MainWindow::successTakeShot()
{
	QMessageBox::information(this, "Info", "Image saved", QMessageBox::Ok);
}

void MainWindow::failedTakeShot()
{
	QMessageBox::critical(this, "Error", "Failed to save image", QMessageBox::Ok);
}


