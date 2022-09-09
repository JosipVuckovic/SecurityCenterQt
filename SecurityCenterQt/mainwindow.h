#pragma once 

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "camerafeed.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void disableAllButtons();
	void successTakeShot();
	void failedTakeShot();
	void setupCameras();
	void terminateAllCameras();
	void startAllCameras();

private slots:
	//void on_<object - name>_<signal - name>(<signal - parameters>); how it needs to look like, can't be generated in designer unlike qt creator
	void on_StartCameras_button_clicked();

	void on_cam1_take_shot_button_clicked();
	void on_cam1_record_button_clicked();

	void on_cam2_take_shot_button_clicked();
	void on_cam2_record_button_clicked();

	void on_cam3_take_shot_button_clicked();
	void on_cam3_record_button_clicked();

	void on_cam4_take_shot_button_clicked();
	void on_cam4_record_button_clicked();

	void on_settings_button_clicked();
private:
	Ui::MainWindowClass ui;	
	CameraFeed* VideoCapture_Cam1;
	CameraFeed* VideoCapture_Cam2;
	CameraFeed* VideoCapture_Cam3;	
	CameraFeed* VideoCapture_Cam4;
	bool recordingCam1 = false;
	bool recordingCam2 = false;
	bool recordingCam3 = false;
	bool recordingCam4 = false;
};

