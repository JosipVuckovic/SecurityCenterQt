#pragma once

#include <qpixmap.h>
#include <qimage.h>
#include <qthread.h>
#include <opencv2/opencv.hpp>
#include "camera.h"
#include "settingswindow.h"

//TODO: In far future: Split into workers according to detection and anonimization Y/N
class CameraFeed : public QThread
{
	Q_OBJECT
public:				
	CameraFeed(Camera cam, QObject* parent = nullptr);
	~CameraFeed(){};

	const QPixmap& pixmap()
	{
		return mPixmap;
	}

	QImage qImageFromOpenCVMat()
	{
		return QImage((unsigned char*)mFrame.data, mFrame.cols, mFrame.rows, QImage::Format_RGB888).rgbSwapped(); //Converts OpenCV BGR to RGB
	}

	Camera& getCameraToModify()
	{
		return mCamera;
	}

	const bool& isIsRecieving()
	{
		return mIsRecieving;
	}

	void setIsRecieving(bool is)
	{
		mIsRecieving = is;
	}

	void setVideoCapture(std::string conVar)
	{
		mVideoCapture = cv::VideoCapture(conVar);
	}

	void setVideoCapture(int conVar)
	{
		mVideoCapture = cv::VideoCapture(conVar);
	}

	void releaseRecording();
	void initRecording();

	bool saveCameraScreenshot();	

signals:
	void newPixmapCaptured();

protected:
	void run() override;
	

private:
	bool mRecording = false;
	bool mIsRecieving = false;
	Camera mCamera;
	QPixmap mPixmap;
	cv::Mat mFrame;
	cv::VideoCapture mVideoCapture;
	cv::Mat mResizedRecordingFrame;	
	cv::VideoWriter oVideoWriter;
};






