#pragma once 

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class CameraFeed;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:

	//void on_<object - name>_<signal - name>(<signal - parameters>); how it needs to look like, can't be generated in designer unlike qt creator
	void on_StartCameras_button_clicked();
	void on_cam1_take_shot_button_clicked();
	void on_cam1_record_button_clicked();

private:
	Ui::MainWindowClass ui;	
	CameraFeed* VideoCapture_Cam1;
	//CameraFeed* VideoCapture_Cam2;
	//CameraFeed* VideoCapture_Cam3;

	//TODO: Remove after testing
	bool recording = false;
};
