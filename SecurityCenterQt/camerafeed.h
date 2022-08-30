#pragma once

#include <qpixmap.h>
#include <qimage.h>
#include <qthread.h>
#include <opencv2/opencv.hpp>

#define HARDCODED_CAMERAID 0

class CameraFeed : public QThread
{
	Q_OBJECT
public:
	CameraFeed(QObject* parent = nullptr);
	
	QPixmap pixmap() 
	{
		return Pixmap;
	}

signals:
	void newPixmapCaptured();

protected:
	void run() override;

private:
	QPixmap Pixmap;
	cv::Mat Frame;
	cv::VideoCapture VideoCapture;

};

