#include "stdafx.h"
#include "camerafeed.h"
#include <opencv2/opencv.hpp>

CameraFeed::CameraFeed(Camera cam, QObject* parent) : QThread{ parent }, mCamera{ cam }
{
	if (cam.getCameraEnumType() == CameraTypeEnum::DIRECT_CONNECT)
	{
		mVideoCapture = cv::VideoCapture(cam.getCameraConnectionString().toInt());
	}
	else
	{
		mVideoCapture = cv::VideoCapture(cam.getCameraConnectionString().toStdString());
	}
}

void CameraFeed::run()
{
	if (mVideoCapture.isOpened())
	{
		mIsRecieving = true;

		while (true)
		{
			mVideoCapture >> mFrame;			

			if (mRecording)
			{	
				cv::resize(mFrame, mResizedRecordingFrame, this->mCamera.getCameraFeedSize());
				cv::putText(mFrame, "[REC]", cv::Point(0, 30), 5, 1, cv::Scalar(0, 0, 225));				
				oVideoWriter.write(mResizedRecordingFrame);
			}
			
			if (!mFrame.empty())
			{				
				mPixmap = QPixmap::fromImage(qImageFromOpenCVMat());
				emit newPixmapCaptured();
			}
		}
	}
	else
	{
		mIsRecieving = false;
		mPixmap = QPixmap::fromImage(QImage(":/MainWindow/noCamera.jpg"));
		emit newPixmapCaptured();
	}
}

void CameraFeed::initRecording(bool rec)
{	
	mRecording = rec;

	std::string outputString = QDir::currentPath().toStdString() + "/" + this->mCamera.getCamerName().toStdString() + "_" + QDateTime::currentDateTime().toString("dd_MM_yy_hh_mm_ss").toStdString() + ".avi";
	int codec = cv::VideoWriter::fourcc('D', 'I', 'V', 'X');
	oVideoWriter = cv::VideoWriter(outputString, codec,this->mCamera.getCameraFPS(), this->mCamera.getCameraFeedSize(), true);
}

void CameraFeed::releaseRecording(bool rec)
{	
	mRecording = rec;

	oVideoWriter.release();
}

bool CameraFeed::saveCameraScreenshot()
{	
	QImage tmp = this->qImageFromOpenCVMat();
	QString outputString = QDir::currentPath()+"/" + this->mCamera.getCamerName()+ "_" + QDateTime::currentDateTime().toString("dd_MM_yy_hh_mm_ss") + ".jpg";
	QImageWriter writer(outputString);
	return writer.write(tmp);
}
