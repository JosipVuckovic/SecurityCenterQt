#include "stdafx.h"
#include "helpers.h"


CameraFeed* InitializeCameraFeed(CameraFeed* camFeed, CameraSettingsResult* camResult, QObject* parent)
{
	if (camResult != nullptr)
	{
		if (camResult->direcltyConnected != nullptr)
		{
			return camFeed = new CameraFeed(*camResult->direcltyConnected, parent);
		}
		else if (camResult->ipcamera != nullptr)
		{
			return camFeed = new CameraFeed(*camResult->ipcamera, parent);
		}
	}
	else
	{
		return camFeed = nullptr;
	}
}

