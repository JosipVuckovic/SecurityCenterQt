#include "stdafx.h"
#include "camerafeed.h"

CameraFeed::CameraFeed(int cameraId, QObject* parent) : QThread{ parent }, VideoCapture{ cameraId }
{}

CameraFeed::CameraFeed(std::string connectionString, QObject* parent) : QThread{ parent }, VideoCapture{ connectionString }
{}

void CameraFeed::run()
{
	if (VideoCapture.isOpened())
	{
		while (true)
		{
			VideoCapture >> Frame;
			if (!Frame.empty())
			{
				//TODO: Maybe move to helper inline function
				Pixmap = QPixmap::fromImage(qImageFromOpenCVMat());
				emit newPixmapCaptured();
			}

		}
	}	
}
