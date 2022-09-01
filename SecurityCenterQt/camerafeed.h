#pragma once

#include <qpixmap.h>
#include <qimage.h>
#include <qthread.h>
#include <opencv2/opencv.hpp>

//TODO: Remove after testing
#define HARDCODED_CAMERAID 0
#define HARDCODED_IP_CAMERA1 "http://192.168.100.15:6677/videofeed?username=CCJDMFKDF&password="
#define HARDCODED_IP_CAMERA2 "http://192.168.100.39:6677/videofeed?username=CCJDMFKDF&password="

//TODO: Split to Ip camera and usb/internal camera
class CameraFeed : public QThread
{
	Q_OBJECT
public:
	CameraFeed(int cameraId, QObject* parent = nullptr);
	CameraFeed(std::string cameraConnectionString, QObject* parent = nullptr);

	QPixmap pixmap()
	{
		return Pixmap;
	}

	QImage inline qImageFromOpenCVMat()
	{
		return QImage((unsigned char*)Frame.data, Frame.cols, Frame.rows, QImage::Format_RGB888).rgbSwapped(); //Converts OpenCV BGR to RGB
	}
	
	void inline setRecordingStatus(bool rec)
	{	
		recording = rec;		
	}
	
	void releaseRecording(bool rec);	
	void initRecording(bool rec);

	bool saveCameraScreenshot();	

signals:
	void newPixmapCaptured();		

protected:
	void run() override;	

private:	
	int CameraId;
	std::string CameraConnectionString;
	QPixmap Pixmap;
	cv::Mat Frame;
	cv::VideoCapture VideoCapture;	
	cv::Mat ResizedRecordingFrame;
	bool recording = false;
	cv::VideoWriter oVideoWriter;	
};






