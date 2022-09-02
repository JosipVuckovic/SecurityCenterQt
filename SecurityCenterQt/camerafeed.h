#pragma once

#include <qpixmap.h>
#include <qimage.h>
#include <qthread.h>
#include <opencv2/opencv.hpp>
#include "camera.h"

//TODO: Remove after testing
#define HARDCODED_CAMERAID 0
#define HARDCODED_IP_CAMERA1 "http://192.168.100.15:6677/videofeed?username=CCJDMFKDF&password="
#define HARDCODED_IP_CAMERA2 "http://192.168.100.39:6677/videofeed?username=CCJDMFKDF&password="


//TODO: In far future: Split into workers according to detection and anonimization Y/N
class CameraFeed : public QThread
{
	Q_OBJECT
public:		
	CameraFeed(DirectlyConnectedCamera& cam, QObject* parent = nullptr);
	CameraFeed(IPCamera& cam, QObject* parent = nullptr);
	
	~CameraFeed(){};

	QPixmap pixmap()
	{
		return Pixmap;
	}

	QImage inline qImageFromOpenCVMat()
	{
		return QImage((unsigned char*)Frame.data, Frame.cols, Frame.rows, QImage::Format_RGB888).rgbSwapped(); //Converts OpenCV BGR to RGB
	}

	void releaseRecording(bool rec);
	void initRecording(bool rec);

	bool saveCameraScreenshot();

signals:
	void newPixmapCaptured();

protected:
	void run() override;

private:
	bool recording = false;
	ICamera Camera;
	QPixmap Pixmap;
	cv::Mat Frame;
	cv::VideoCapture VideoCapture;
	cv::Mat ResizedRecordingFrame;	
	cv::VideoWriter oVideoWriter;
};






