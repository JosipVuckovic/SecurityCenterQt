#pragma once

#include <QDialog>
#include "ui_settingswindow.h"
#include "camera.h"

#define CAM1 "CAMERA1"
#define CAM2 "CAMERA2"
#define CAM3 "CAMERA3"
#define CAM4 "CAMERA4"
#define CAMERA_NAME "CAMERA_NAME"
#define CAMERA_TYPE "CAMERA_TYPE"
#define CAMERA_FEED_SIZE_H "CAMERA_FEED_SIZE_H" 
#define CAMERA_FEED_SIZE_W "CAMERA_FEED_SIZE_W" 
#define CAMERA_FPS "CAMERA_FPS"
#define CAMERA_IS_COLOR "CAMERA_IS_COLOR"
#define CAMERA_CONNVALL "CAMERA_CONNECTION"

struct CameraSettingsResult
{

	~CameraSettingsResult(){};

	IPCamera* ipcamera;
	DirectlyConnectedCamera* direcltyConnected;
};

CameraSettingsResult* loadSettingsFromRegistry(QString grpName);

class SettingsWindow : public QDialog, public Ui::SettingsWindowClass
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = nullptr);
	~SettingsWindow();

	void setDialogValidators();	
	bool saveSettingsToRegistry(QString grpName, QVariant camType, QString name, int fps, int w, int h, QVariant camId, bool isColor);

private slots:
	void on_cam1_saveChanges_button_clicked();
	void on_cam1_Type_comboBox_currentIndexChanged(int index);
private:
	Ui::SettingsWindowClass ui;
};
