#include "stdafx.h"
#include "camerafeed.h"
#include <opencv2/opencv.hpp>
#include "globalstrings.h"

//OpenCV related 
//OpenCV uses BGR scalars, but we flip that on images with QT so watch out for that
//use G when you want B and B when you want G
const static int& _fontFace = 5;
const static int& _fontScale = 1;
const static cv::Point& _textOriginPoint = cv::Point(0, 30);
const static cv::Scalar _redColor = { 0, 0, 255 };
const static cv::Scalar _greenColor = { 0, 255, 0 };
const static cv::Scalar _blueColor = { 255, 0,0 };
const static char* _DIVIX[4] = { "D","I","V","X" };

const static double& _detection_scaleFactor = 1.1;
const static int& _detection_minNeighbors = 2;
const static cv::Size& _detection_minSize = cv::Size(30, 30);

const static int& _lineThincknes = 3;
const static int& _lineType = 6;

const static cv::Size& _gausian_kernelSize = cv::Size(0, 0);
const static int& _gausian_sigma = 35;


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
	cv::CascadeClassifier faceCascade;
	if (this->mCamera.getIsEnabled())
	{
		QTemporaryDir tempDir;
		if (tempDir.isValid()) {
			const QString tempFile = tempDir.path() + SCStrings::_slash + SCStrings::_haarFileName;
			if (QFile::copy(SCStrings::_QtResurceHaar, tempFile)) //File will autoclean when exits the scope
			{
				faceCascade.load(tempFile.toStdString()); 
			}
		}
	}
	
	if (mVideoCapture.isOpened())
	{
		mIsRecieving = true;

		while (true)
		{
			mVideoCapture >> mFrame;			

			if (mRecording)
			{	
				cv::resize(mFrame, mResizedRecordingFrame, this->mCamera.getCameraFeedSize());
				cv::putText(mFrame, SCStrings::_rec, _textOriginPoint, _fontFace, _fontScale, _redColor);
				oVideoWriter.write(mResizedRecordingFrame);
			}	
			
			if (!faceCascade.empty())
			{
				std::vector<cv::Rect> faces;
				faceCascade.detectMultiScale(mFrame, faces, _detection_scaleFactor, _detection_minNeighbors, cv::CASCADE_SCALE_IMAGE, _detection_minSize);

				for (int i = 0; i < faces.size(); ++i)
				{					
					cv::rectangle(mFrame, faces[i], _greenColor, _lineThincknes, _lineType);
					cv::GaussianBlur(mFrame(faces[i]), mFrame(faces[i]), _gausian_kernelSize, _gausian_sigma);
				}
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
		mPixmap = QPixmap::fromImage(QImage(SCStrings::_QtResurceNoCam));
		emit newPixmapCaptured();
	}
}

void CameraFeed::initRecording(bool rec)
{	
	mRecording = rec;

	std::string outputString = QDir::currentPath().toStdString() + SCStrings::_slash + this->mCamera.getCamerName().toStdString() + SCStrings::_underscore + QDateTime::currentDateTime().toString(SCStrings::_dateTimeFormat).toStdString() + SCStrings::_dotAvi;
	int codec = cv::VideoWriter::fourcc(*_DIVIX[0], *_DIVIX[1], *_DIVIX[2], *_DIVIX[3]);
	oVideoWriter = cv::VideoWriter(outputString, codec,this->mCamera.getCameraFPS(), this->mCamera.getCameraFeedSize(), this->mCamera.getIsColor());
}

void CameraFeed::releaseRecording(bool rec)
{	
	mRecording = rec;

	oVideoWriter.release();
}

bool CameraFeed::saveCameraScreenshot()
{	
	QImage tmp = this->qImageFromOpenCVMat();
	QString outputString = QDir::currentPath()+ SCStrings::_slash + this->mCamera.getCamerName()+ SCStrings::_underscore + QDateTime::currentDateTime().toString(SCStrings::_dateTimeFormat) + SCStrings::_dotJpg;
	QImageWriter writer(outputString);
	return writer.write(tmp);
}
