#include "stdafx.h"
#include "mainwindow.h"
#include "camerafeed.h"

MainWindow::MainWindow(QWidget* parent)	: QMainWindow(parent)
{
	ui.setupUi(this);

	//TODO: Implement Settings
	//TODO: Read camera connection data from settings
	//TODO: PROP: Just create more video captures or use some sort of worer??
			
	VideoCapture_Cam1 = new CameraFeed(HARDCODED_CAMERAID, this);	
	//VideoCapture_Cam2 = new CameraFeed(HARDCODED_IP_CAMERA1, this);	
	//VideoCapture_Cam3 = new CameraFeed(HARDCODED_IP_CAMERA2, this);


	//TODO: Read W/H from settings	
	//TODO: PROP:  On double click on one, have it in full screen? Y/N
		
	connect(VideoCapture_Cam1, &CameraFeed::newPixmapCaptured, this, [&]() {
		ui.cam1->setPixmap(VideoCapture_Cam1->pixmap().scaled(640, 480));
		});	

	//connect(VideoCapture_Cam2, &CameraFeed::newPixmapCaptured, this, [&]() {
	//	ui.cam2->setPixmap(VideoCapture_Cam2->pixmap().scaled(640, 480));
	//	});

	//connect(VideoCapture_Cam3, &CameraFeed::newPixmapCaptured, this, [&]() {
	//	ui.cam3->setPixmap(VideoCapture_Cam3->pixmap().scaled(640, 480));
	//	});
}

void MainWindow::on_StartCameras_button_clicked()
{
	VideoCapture_Cam1->start();
	//VideoCapture_Cam2->start();
	//VideoCapture_Cam3->start();
}

MainWindow::~MainWindow()
{
	VideoCapture_Cam1->terminate();
	/*VideoCapture_Cam2->terminate();
	VideoCapture_Cam3->terminate();	*/
}

void MainWindow::on_cam1_take_shot_button_clicked()
{
	QImage tmp = VideoCapture_Cam1->qImageFromOpenCVMat();	
	QString outputString = QDir::currentPath() +"/cam1_"+QTime::currentTime().toString("hh_mm_ss")+".jpg";
	
	QImageWriter writer(outputString);
	if (writer.write(tmp))
	{
		//TODO: Some dialog notify success and fail in else
		//TODO: Move to helper class
	}	
}

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
