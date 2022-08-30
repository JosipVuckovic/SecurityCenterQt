#pragma once 

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class CameraFeed;

class MainWindow : public QMainWindow
{
    Q_OBJECT
                
public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    
    //void on_<object - name>_<signal - name>(<signal - parameters>); how it needs to look like, can't be generated in designer unlike qt creator
    void on_StartCameras_button_clicked();

private:
    Ui::MainWindowClass ui;
    CameraFeed *VideoCapture;
};
