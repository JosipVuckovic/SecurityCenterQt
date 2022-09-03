# SecurityCenterQt

## Description
Small security sute that allows for streaming video from 4 directly connected or 4 ip cameras.
There is posibility to take pictures from cameras and to record video from each camera.
All settings are writen to local windows registry.

Writen in c++ using QT framework and OpenCV library.

## Requirements
### To develop
- [QT 6.3](https://www.qt.io/download)
- [QT visual studio integration](https://www.qt.io/blog/qt-vs-tools-for-visual-studio-2022)

## To release
- [QT Windows release](https://doc.qt.io/qt-6/windows-deployment.html#static-linking)
### Easiest
Find path to Drive:\Qt\6.3.1\msvc2019_64\bin <br/>
Build QT as in documentation  <br/>
In powershell:  <br/>
set PATH={YourQT \bin path} <br/>
windeployqt.exe  {pathToSolution\x64\Release} <br/>



  
  

  
