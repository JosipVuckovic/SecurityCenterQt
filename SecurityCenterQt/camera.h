#pragma once

#include <string>
#include <opencv2/opencv.hpp>

enum CameraTypeEnum
{
	IP_CAMERA = 1,
	DIRECT_CONNECT = 2
};


class Camera
{
public:
	Camera() {};
	~Camera() {};

	const QString& getCameraConnectionString()
	{
		return mCameraConnectionString;
	}

	const QString& getCamerName()
	{
		return mCameraName;
	}

	const cv::Size& getCameraFeedSize()
	{
		return mCameraFeedSize;
	}

	const int& getCameraFPS()
	{
		return mCameraFPS;
	}

	const bool& getIsEnabled()
	{
		return mIsEnabled;
	}

	const CameraTypeEnum& getCameraEnumType()
	{
		return mCameraType;
	}

	const bool& getIsColor()
	{
		return mIsColor;
	}

	void setCameraName(QString name)
	{
		mCameraName = name;
	}

	void setCameraFPS(int fps)
	{
		mCameraFPS = fps;
	}

	void setCameraFeedSize(int w, int h)
	{
		mCameraFeedSize.width = w;
		mCameraFeedSize.height = h;
	}

	void setCameraTypeEnum(CameraTypeEnum type)
	{
		mCameraType = type;
	}

	void setIsColor(bool is)
	{

		mIsColor = is;
	}

	void setIsEnabled(bool ena)
	{
		mIsEnabled = ena;
	}

	void setCameraConnectionString(QString conVal)
	{
		mCameraConnectionString = conVal;
	}

private:
	QString mCameraName;
	QString mCameraConnectionString;
	CameraTypeEnum mCameraType;
	cv::Size mCameraFeedSize;
	int mCameraFPS;
	bool mIsColor = true;
	bool mIsEnabled = false;
};

