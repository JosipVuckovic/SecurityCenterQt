#include "stdafx.h"
#include "camerafeed.h"
#include <opencv2/opencv.hpp>

CameraFeed::CameraFeed(DirectlyConnectedCamera& cam, QObject* parent) : QThread{ parent }, VideoCapture{ cam.getConnectionValue() }, Camera{cam}{}
CameraFeed::CameraFeed(IPCamera& cam, QObject* parent) : QThread{ parent }, VideoCapture{ cam.getConnectionValue() }, Camera{ cam }{}

void CameraFeed::run()
{
	if (VideoCapture.isOpened())
	{
		while (true)
		{
			VideoCapture >> Frame;

			if (recording)
			{	
				cv::resize(Frame, ResizedRecordingFrame, this->Camera.getCameraFeedSize());
				cv::putText(Frame, "[REC]", cv::Point(0, 30), 5, 1, cv::Scalar(0, 0, 225));
				oVideoWriter.write(ResizedRecordingFrame);
			}
			
			if (!Frame.empty())
			{				
				Pixmap = QPixmap::fromImage(qImageFromOpenCVMat());
				emit newPixmapCaptured();
			}

		}
	}
	else
	{
		Pixmap = QPixmap::fromImage(QImage(":/MainWindow/noCamera.jpg"));
		emit newPixmapCaptured();
	}
}

void CameraFeed::initRecording(bool rec)
{	
	recording = rec;

	std::string outputString = QDir::currentPath().toStdString() + "/" + this->Camera.getCamerName()+ "_" + QDateTime::currentDateTime().toString("dd_MM_yy_hh_mm_ss").toStdString() + ".avi";
	int codec = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');
	oVideoWriter = cv::VideoWriter(outputString, codec,this->Camera.getCameraFPS(), this->Camera.getCameraFeedSize(), true);
}

void CameraFeed::releaseRecording(bool rec)
{	
	recording = rec;

	oVideoWriter.release();
}

bool CameraFeed::saveCameraScreenshot()
{	
	QImage tmp = this->qImageFromOpenCVMat();
	QString outputString = QDir::currentPath()+"/" + QString::fromStdString(this->Camera.getCamerName())+ "_" + QDateTime::currentDateTime().toString("dd_MM_yy_hh_mm_ss") + ".jpg";
	QImageWriter writer(outputString);
	return writer.write(tmp);
}



