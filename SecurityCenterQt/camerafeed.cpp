#include "stdafx.h"
#include "camerafeed.h"
#include <opencv2/opencv.hpp>


CameraFeed::CameraFeed(int cameraId, QObject* parent) : QThread{ parent }, VideoCapture{ cameraId }{}

CameraFeed::CameraFeed(std::string connectionString, QObject* parent) : QThread{ parent }, VideoCapture{ connectionString }{}

void CameraFeed::run()
{		
	if (VideoCapture.isOpened())
	{
		while (true)
		{
			VideoCapture >> Frame;

			if (recording)
			{				
				//TODO: move stuff to camera class
				cv::Size fSize(static_cast<int>(640), static_cast<int>(480));
				cv::resize(Frame, ResizedRecordingFrame, fSize);
				oVideoWriter.write(ResizedRecordingFrame);
			}
			
			if (!Frame.empty())
			{				
				Pixmap = QPixmap::fromImage(qImageFromOpenCVMat());
				emit newPixmapCaptured();
			}

		}
	}	
}

void CameraFeed::initRecording(bool rec)
{
	setRecordingStatus(rec);

	std::string outputString = QDir::currentPath().toStdString() + "/cam1_video_" + QTime::currentTime().toString("hh_mm_ss").toStdString() + ".avi";
	double dWidth = 640; //get the width of frames of the video
	double dHeight = 480; //get the height of frames of the video
	cv::Size fSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	int codec = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');
	oVideoWriter = cv::VideoWriter(outputString, codec, 10, fSize, true);
}

void CameraFeed::releaseRecording(bool rec)
{
	setRecordingStatus(rec);
	oVideoWriter.release();
}

bool CameraFeed::saveCameraScreenshot()
{
	//TODO: Need cameraName in settings
	QImage tmp = this->qImageFromOpenCVMat();
	QString outputString = QDir::currentPath() + "/cam1_" + QTime::currentTime().toString("hh_mm_ss") + ".jpg";
	QImageWriter writer(outputString);
	return writer.write(tmp);
}


