#include "stdafx.h"
#include "settingswindow.h"
#include "camera.h"

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

	//CRY!!!
	CameraSettingsResult* loadedSettings = loadSettingsFromRegistry(CAM1);
	if (loadedSettings != nullptr)
	{
		auto isIP = loadedSettings->direcltyConnected == nullptr;
		auto camSettings = isIP ? static_cast<ICamera>(*loadedSettings->ipcamera) : static_cast<ICamera>(*loadedSettings->direcltyConnected);

		auto test = camSettings.getCameraEnumType();
		ui.cam1_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(camSettings.getCameraEnumType()));
		ui.cam1_lineEdit_Name->setText(QString::fromStdString(camSettings.getCamerName()));
		ui.cam1_lineEdit_FPS->setText(QString::number(camSettings.getCameraFPS()));
		auto camSize = camSettings.getCameraFeedSize();
		ui.cam1_lineEdit_Width->setText(QString::number(camSize.width));
		ui.cam1_lineEdit_Height->setText(QString::number(camSize.height));

		//CRY Again..
		QString conVal;
		if (isIP)
		{
			conVal = QString::fromStdString(loadedSettings->ipcamera->getConnectionValue());
		}
		else
		{
			conVal = QString::number(loadedSettings->direcltyConnected->getConnectionValue());
		}

		ui.cam1_lineEdit_Connection->setText(conVal);
		ui.cam1_checkBox_Color->setChecked(camSettings.getIsColor());
	}	

	ui.cam2_lineEdit_FPS->setValidator(intValFPS);
	ui.cam2_lineEdit_Height->setValidator(intValResolution);
	ui.cam2_lineEdit_Width->setValidator(intValResolution);

	ui.cam2_Type_comboBox->addItem("Direct/USB", CameraTypeEnum::DIRECT_CONNECT);
	ui.cam2_Type_comboBox->addItem("IP Camera", CameraTypeEnum::IP_CAMERA);

	loadedSettings = loadSettingsFromRegistry(CAM2);
	if (loadedSettings != nullptr)
	{
		auto isIP = loadedSettings->direcltyConnected == nullptr;
		auto camSettings = isIP ? static_cast<ICamera>(*loadedSettings->ipcamera) : static_cast<ICamera>(*loadedSettings->direcltyConnected);

		auto test = camSettings.getCameraEnumType();
		ui.cam2_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(camSettings.getCameraEnumType()));
		ui.cam2_lineEdit_Name->setText(QString::fromStdString(camSettings.getCamerName()));
		ui.cam2_lineEdit_FPS->setText(QString::number(camSettings.getCameraFPS()));
		auto camSize = camSettings.getCameraFeedSize();
		ui.cam2_lineEdit_Width->setText(QString::number(camSize.width));
		ui.cam2_lineEdit_Height->setText(QString::number(camSize.height));

		//CRY Again..
		QString conVal;
		if (isIP)
		{
			conVal = QString::fromStdString(loadedSettings->ipcamera->getConnectionValue());
		}
		else
		{
			conVal = QString::number(loadedSettings->direcltyConnected->getConnectionValue());
		}

		ui.cam2_lineEdit_Connection->setText(conVal);
		ui.cam2_checkBox_Color->setChecked(camSettings.getIsColor());
	}

	ui.cam3_lineEdit_FPS->setValidator(intValFPS);
	ui.cam3_lineEdit_Height->setValidator(intValResolution);
	ui.cam3_lineEdit_Width->setValidator(intValResolution);

	ui.cam3_Type_comboBox->addItem("Direct/USB", CameraTypeEnum::DIRECT_CONNECT);
	ui.cam3_Type_comboBox->addItem("IP Camera", CameraTypeEnum::IP_CAMERA);

	loadedSettings = loadSettingsFromRegistry(CAM3);
	if (loadedSettings != nullptr)
	{
		auto isIP = loadedSettings->direcltyConnected == nullptr;
		auto camSettings = isIP ? static_cast<ICamera>(*loadedSettings->ipcamera) : static_cast<ICamera>(*loadedSettings->direcltyConnected);

		auto test = camSettings.getCameraEnumType();
		ui.cam3_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(camSettings.getCameraEnumType()));
		ui.cam3_lineEdit_Name->setText(QString::fromStdString(camSettings.getCamerName()));
		ui.cam3_lineEdit_FPS->setText(QString::number(camSettings.getCameraFPS()));
		auto camSize = camSettings.getCameraFeedSize();
		ui.cam3_lineEdit_Width->setText(QString::number(camSize.width));
		ui.cam3_lineEdit_Height->setText(QString::number(camSize.height));

		//CRY Again..
		QString conVal;
		if (isIP)
		{
			conVal = QString::fromStdString(loadedSettings->ipcamera->getConnectionValue());
		}
		else
		{
			conVal = QString::number(loadedSettings->direcltyConnected->getConnectionValue());
		}

		ui.cam3_lineEdit_Connection->setText(conVal);
		ui.cam3_checkBox_Color->setChecked(camSettings.getIsColor());
	}

	ui.cam4_lineEdit_FPS->setValidator(intValFPS);
	ui.cam4_lineEdit_Height->setValidator(intValResolution);
	ui.cam4_lineEdit_Width->setValidator(intValResolution);

	ui.cam4_Type_comboBox->addItem("Direct/USB", CameraTypeEnum::DIRECT_CONNECT);
	ui.cam4_Type_comboBox->addItem("IP Camera", CameraTypeEnum::IP_CAMERA);

	loadedSettings = loadSettingsFromRegistry(CAM3);
	if (loadedSettings != nullptr)
	{
		auto isIP = loadedSettings->direcltyConnected == nullptr;
		auto camSettings = isIP ? static_cast<ICamera>(*loadedSettings->ipcamera) : static_cast<ICamera>(*loadedSettings->direcltyConnected);

		auto test = camSettings.getCameraEnumType();
		ui.cam4_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(camSettings.getCameraEnumType()));
		ui.cam4_lineEdit_Name->setText(QString::fromStdString(camSettings.getCamerName()));
		ui.cam4_lineEdit_FPS->setText(QString::number(camSettings.getCameraFPS()));
		auto camSize = camSettings.getCameraFeedSize();
		ui.cam4_lineEdit_Width->setText(QString::number(camSize.width));
		ui.cam4_lineEdit_Height->setText(QString::number(camSize.height));

		//CRY Again..
		QString conVal;
		if (isIP)
		{
			conVal = QString::fromStdString(loadedSettings->ipcamera->getConnectionValue());
		}
		else
		{
			conVal = QString::number(loadedSettings->direcltyConnected->getConnectionValue());
		}

		ui.cam4_lineEdit_Connection->setText(conVal);
		ui.cam4_checkBox_Color->setChecked(camSettings.getIsColor());
	}

}

SettingsWindow::~SettingsWindow() {}

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
		showOkDialog(this);
	}
	else
	{
		showFailedDialog(this);
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
		camera->setCameraTypeEnum(type);
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
		camera->setCameraTypeEnum(type);
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

void SettingsWindow::showOkDialog(QWidget* parent)
{
	QMessageBox::information(parent, "Success", "Camera settings saved successfully", "OK");
}

void SettingsWindow::showFailedDialog(QWidget* parent)
{
	QMessageBox::critical(parent, "ERROR", "Failed to save camera settings \n\r Contact your support! ", "OK");
}