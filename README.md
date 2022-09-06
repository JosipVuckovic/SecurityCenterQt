# SecurityCenterQt

## Description
Small security suites that allows for streaming video from 4 directly connected or 4 IP cameras.
There is possibility to take pictures from cameras and to record video from each camera.
All settings are written to the local windows registry.

Written in c++ using the QT framework and OpenCV library.

###Settings:
Go to settings and set up cameras you want to use, initial program is not set up to use any camera.
CameraType - tells the program how to interpret connection value
Name - User designation of camera
Connection - connection string to connect to IP camera, or int index locally connected camera (0 is built in camera)
FPS and Resoultion fields - used for recording, does not impact camera streaming that is always set to 640 x 480

###Recording
The program will record video and take pictures to the root program folder.


## Requirements
### To develop
- [QT 6.3](https://www.qt.io/download)
- [QT visual studio integration](https://www.qt.io/blog/qt-vs-tools-for-visual-studio-2022)

Download QT version 6.3. <br/>
Install visual studio extension that integrates QT into preferred VS. version

## To release
- [QT, Windows deployment](https://doc.qt.io/qt-6/windows-deployment.html#static-linking)
### Easiest
Find path to Drive:\Qt\6.3.1\msvc2019_64\bin <br/>
Build QT as in the documentation  <br/>
In powershell:  <br/>
Set PATH={YourQT \bin path} <br/>
windeployqt.exe  {pathToSolution\x64\Release} <br/>



  
  

  
