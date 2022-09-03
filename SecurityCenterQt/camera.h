#pragma once

#include <string>
#include <opencv2/opencv.hpp>

enum CameraTypeEnum
{
	IP_CAMERA = 1,
	DIRECT_CONNECT = 2
};


class ICamera
{	
public:
	virtual ~ICamera(){};
	const std::string getCamerName()
	{
		return CameraName;
	}

	const cv::Size getCameraFeedSize()
	{
		return CameraFeedSize;
	}

	const int getCameraFPS()
	{
		return CameraFPS;
	}

	const bool getIsEnabled()
	{
		return IsEnabled;
	}

	const CameraTypeEnum getCameraEnumType()
	{
		return CameraType;
	}

	const bool getIsColor()
	{
		return IsColor;
	}

	void setCameraName(std::string name)
	{
		CameraName = name;
	}

	void setCameraFPS(int fps)
	{
		CameraFPS = fps;
	}		 

	void setCameraFeedSize(int w, int h)
	{
		CameraFeedSize.width = w;
		CameraFeedSize.height = h;
	}

	void setCameraTypeEnum(CameraTypeEnum type)
	{
		CameraType = type;
	}

	void setIsColor(bool is)
	{

		IsColor = is;
	}

	void setIsEnabled(bool ena)
	{
		IsEnabled = ena;
	}
	
private:
	std::string CameraName;
	CameraTypeEnum CameraType;
	cv::Size CameraFeedSize;
	int CameraFPS;
	bool IsColor = true;
	bool IsEnabled = false;
};

class IPCamera : public ICamera
{
public:

	IPCamera(){};
	~IPCamera(){};

	const std::string getConnectionValue() 
	{
		return CameraConnectionString;
	}
	void setConnectionValue(std::string connVal)
	{
		CameraConnectionString = connVal;
	}
	
private:
	std::string CameraConnectionString;
	
};

class DirectlyConnectedCamera : public ICamera
{
public:

	DirectlyConnectedCamera(){};
	~DirectlyConnectedCamera() {};

	const int getConnectionValue()
	{
		return CameraId;
	}
	void setConnectionValue(int camId)
	{
		CameraId = camId;
	}

private:
	int CameraId;
};

