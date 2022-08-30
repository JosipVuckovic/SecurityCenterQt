#include "stdafx.h"
#include "camerafeed.h"

CameraFeed::CameraFeed(QObject* parent) : QThread{ parent }, VideoCapture{ HARDCODED_CAMERAID }
{

}

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
				Pixmap = QPixmap::fromImage(QImage((unsigned char*)Frame.data, Frame.cols, Frame.rows, QImage::Format_RGB888).rgbSwapped()); //Converts OpenCV BGR to RGB
				emit newPixmapCaptured();
			}

		}
	}
}
