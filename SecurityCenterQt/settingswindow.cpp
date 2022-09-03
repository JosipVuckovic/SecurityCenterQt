#include "stdafx.h"
#include "settingswindow.h"
#include "camera.h"
#include <variant>

SettingsWindow::SettingsWindow(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QIntValidator* intValResolution = new QIntValidator(320, 1080, this);
	QIntValidator* intValFPS = new QIntValidator(1, 60, this);

	
	ui.cam1_lineEdit_FPS->setValidator(intValFPS);
	ui.cam1_lineEdit_Height->setValidator(intValResolution);
	ui.cam1_lineEdit_Width->setValidator(intValResolution);

	ui.cam1_Type_comboBox->addItem("Direct/USB", CameraTypeEnum::DIRECT_CONNECT);
	ui.cam1_Type_comboBox->addItem("IP Camera", CameraTypeEnum::IP_CAMERA);
}

SettingsWindow::~SettingsWindow()
{}

void SettingsWindow::setDialogValidators()
{

}

void SettingsWindow::on_cam1_saveChanges_button_clicked()
{
	if (saveSettingsToRegistry(
		CAM1,
		ui.cam1_Type_comboBox->currentData(),
		ui.cam1_lineEdit_Name->text(),
		ui.cam1_lineEdit_FPS->text().toInt(),
		ui.cam1_lineEdit_Width->text().toInt(),
		ui.cam1_lineEdit_Height->text().toInt(),
		ui.cam1_lineEdit_Connection->text(),
		ui.cam1_checkBox_Color->isChecked()))
	{
		QMessageBox::information(this, "Success", "", "OK");
	}
	else
	{
		QMessageBox::critical(this, "ERROR", "Failed to save CAMERA1 settings \n\r Contact your support! ", "OK");
	}

}

void SettingsWindow::on_cam1_Type_comboBox_currentIndexChanged(int index)
{
	if (index == 0)
	{
		ui.cam1_lineEdit_Connection->setValidator(new QIntValidator(0, 100, this));
	}
	else
	{
		ui.cam1_lineEdit_Connection->setValidator(nullptr);
	}

}

bool SettingsWindow::saveSettingsToRegistry(QString grpName, QVariant camType, QString name, int fps, int w, int h, QVariant camId, bool isColor)
{
	try
	{
		QSettings settings;
		settings.beginGroup(grpName);
		settings.setValue(CAMERA_TYPE, camType);
		settings.setValue(CAMERA_NAME, name);
		settings.setValue(CAMERA_FPS, fps);
		settings.setValue(CAMERA_FEED_SIZE_W, w);
		settings.setValue(CAMERA_FEED_SIZE_H, h);
		settings.setValue(CAMERA_CONNVALL, camId);
		settings.setValue(CAMERA_IS_COLOR, isColor);
		settings.endGroup();

		return true;
	}
	catch (const std::exception&)
	{
		//should log or show to user, but we wont, no time left...
		return false;
	}
}

CameraSettingsResult* loadSettingsFromRegistry(QString grpName)
{

	QSettings settings;
	CameraSettingsResult* result = new CameraSettingsResult();
	result->ipcamera = nullptr;
	result->direcltyConnected = nullptr;

	settings.beginGroup(grpName);	

	CameraTypeEnum type = static_cast<CameraTypeEnum>(settings.value(CAMERA_TYPE).toInt());

	if (type == CameraTypeEnum::IP_CAMERA)
	{
		IPCamera* camera = new IPCamera();
		camera->setCameraFeedSize(settings.value(CAMERA_FEED_SIZE_W).toInt(), settings.value(CAMERA_FEED_SIZE_H).toInt());
		camera->setCameraFPS(settings.value(CAMERA_FPS).toInt());
		camera->setCameraName(settings.value(CAMERA_NAME).toString().toStdString());
		camera->setConnectionValue(settings.value(CAMERA_CONNVALL).toString().toStdString());
		camera->setIsColor(settings.value(CAMERA_IS_COLOR).toBool());
		settings.endGroup();

		result->ipcamera = camera;
		return result;
	}

	if (type == CameraTypeEnum::DIRECT_CONNECT)
	{
		DirectlyConnectedCamera* camera = new DirectlyConnectedCamera();
		camera->setCameraFeedSize(settings.value(CAMERA_FEED_SIZE_W).toInt(), settings.value(CAMERA_FEED_SIZE_H).toInt());
		camera->setCameraFPS(settings.value(CAMERA_FPS).toInt());
		camera->setCameraName(settings.value(CAMERA_NAME).toString().toStdString());
		camera->setConnectionValue(settings.value(CAMERA_CONNVALL).toInt());
		camera->setIsColor(settings.value(CAMERA_IS_COLOR).toBool());
		settings.endGroup();

		result->direcltyConnected = camera;
		return result;
	}

	return nullptr;
	
}
