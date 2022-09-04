#pragma once

#include <qpixmap.h>
#include <qimage.h>
#include <qthread.h>
#include <opencv2/opencv.hpp>
#include "camera.h"
#include "settingswindow.h"

//TODO: Remove after testing
#define HARDCODED_IP_CAMERA1 "http://192.168.100.15:6677/videofeed?username=CCJDMFKDF&password="
#define HARDCODED_IP_CAMERA2 "http://192.168.100.39:6677/videofeed?username=CCJDMFKDF&password="

//TODO: In far future: Split into workers according to detection and anonimization Y/N
class CameraFeed : public QThread
{
	Q_OBJECT
public:		
	
	//CameraFeed(Camera& cam, QObject* parent = nullptr);
	CameraFeed(Camera cam, QObject* parent = nullptr);
	~CameraFeed(){};

	QPixmap pixmap()
	{
		return mPixmap;
	}

	QImage qImageFromOpenCVMat()
	{
		return QImage((unsigned char*)mFrame.data, mFrame.cols, mFrame.rows, QImage::Format_RGB888).rgbSwapped(); //Converts OpenCV BGR to RGB
	}

	const bool isCameraSet()
	{
		return mCamera.getIsEnabled();
	}

	void releaseRecording(bool rec);
	void initRecording(bool rec);

	bool saveCameraScreenshot();	

signals:
	void newPixmapCaptured();

protected:
	void run() override;
	

private:
	bool mRecording = false;
	Camera mCamera;
	QPixmap mPixmap;
	cv::Mat mFrame;
	cv::VideoCapture mVideoCapture;
	cv::Mat mResizedRecordingFrame;	
	cv::VideoWriter oVideoWriter;
};






