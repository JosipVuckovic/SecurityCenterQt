#include "stdafx.h"
#include "settingswindow.h"
#include "camera.h"
#include "globalstrings.h"

const int& _minimumIndex = 0;
const int& _maximumIndex = 100;
const int& _minimumFPS = 1;
const int& _maximumFPS = 60;
const int& _minimumResolution = 320;
const int& _maximumResolution = 1080;


SettingsWindow::SettingsWindow(QWidget* parent) : QDialog{ parent }
{
	ui.setupUi(this);	
	intValResolution.setRange(_minimumResolution, _maximumResolution);
	intValFPS.setRange(_minimumFPS, _maximumFPS);
	intIndex.setRange(_minimumIndex, _maximumIndex);
	fillDataForForm();
}

SettingsWindow::~SettingsWindow()
{
	
}

void SettingsWindow::fillDataForForm()
{
	ui.cam1_lineEdit_FPS->setValidator(&intValFPS);
	ui.cam1_lineEdit_Height->setValidator(&intValResolution);
	ui.cam1_lineEdit_Width->setValidator(&intValResolution);

	ui.cam1_Type_comboBox->addItem(SCStrings::_directCam, CameraTypeEnum::DIRECT_CONNECT);
	ui.cam1_Type_comboBox->addItem(SCStrings::_IPcam, CameraTypeEnum::IP_CAMERA);

	Camera loadedSettings = loadSettingsFromRegistry(SCStrings::_CAM1);

	ui.cam1_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(loadedSettings.getCameraEnumType()));
	ui.cam1_lineEdit_Name->setText(loadedSettings.getCamerName());
	ui.cam1_lineEdit_FPS->setText(QString::number(loadedSettings.getCameraFPS()));
	auto camSize = loadedSettings.getCameraFeedSize();
	ui.cam1_lineEdit_Width->setText(QString::number(camSize.width));
	ui.cam1_lineEdit_Height->setText(QString::number(camSize.height));
	ui.cam1_lineEdit_Connection->setText(loadedSettings.getCameraConnectionString());
	ui.cam1_checkBox_Color->setChecked(loadedSettings.getIsColor());
	ui.cam1_Anon->setChecked(loadedSettings.getIsEnabled());


	ui.cam2_lineEdit_FPS->setValidator(&intValFPS);
	ui.cam2_lineEdit_Height->setValidator(&intValResolution);
	ui.cam2_lineEdit_Width->setValidator(&intValResolution);

	ui.cam2_Type_comboBox->addItem(SCStrings::_directCam, CameraTypeEnum::DIRECT_CONNECT);
	ui.cam2_Type_comboBox->addItem(SCStrings::_IPcam, CameraTypeEnum::IP_CAMERA);

	loadedSettings = loadSettingsFromRegistry(SCStrings::_CAM2);

	ui.cam2_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(loadedSettings.getCameraEnumType()));
	ui.cam2_lineEdit_Name->setText(loadedSettings.getCamerName());
	ui.cam2_lineEdit_FPS->setText(QString::number(loadedSettings.getCameraFPS()));
	camSize = loadedSettings.getCameraFeedSize();
	ui.cam2_lineEdit_Width->setText(QString::number(camSize.width));
	ui.cam2_lineEdit_Height->setText(QString::number(camSize.height));
	ui.cam2_lineEdit_Connection->setText(loadedSettings.getCameraConnectionString());
	ui.cam2_checkBox_Color->setChecked(loadedSettings.getIsColor());
	ui.cam2_Anon->setChecked(loadedSettings.getIsEnabled());


	ui.cam3_lineEdit_FPS->setValidator(&intValFPS);
	ui.cam3_lineEdit_Height->setValidator(&intValResolution);
	ui.cam3_lineEdit_Width->setValidator(&intValResolution);

	ui.cam3_Type_comboBox->addItem(SCStrings::_directCam, CameraTypeEnum::DIRECT_CONNECT);
	ui.cam3_Type_comboBox->addItem(SCStrings::_IPcam, CameraTypeEnum::IP_CAMERA);

	loadedSettings = loadSettingsFromRegistry(SCStrings::_CAM3);

	ui.cam3_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(loadedSettings.getCameraEnumType()));
	ui.cam3_lineEdit_Name->setText(loadedSettings.getCamerName());
	ui.cam3_lineEdit_FPS->setText(QString::number(loadedSettings.getCameraFPS()));
	camSize = loadedSettings.getCameraFeedSize();
	ui.cam3_lineEdit_Width->setText(QString::number(camSize.width));
	ui.cam3_lineEdit_Height->setText(QString::number(camSize.height));
	ui.cam3_lineEdit_Connection->setText(loadedSettings.getCameraConnectionString());
	ui.cam3_checkBox_Color->setChecked(loadedSettings.getIsColor());


	ui.cam4_lineEdit_FPS->setValidator(&intValFPS);
	ui.cam4_lineEdit_Height->setValidator(&intValResolution);
	ui.cam4_lineEdit_Width->setValidator(&intValResolution);

	ui.cam4_Type_comboBox->addItem(SCStrings::_directCam, CameraTypeEnum::DIRECT_CONNECT);
	ui.cam4_Type_comboBox->addItem(SCStrings::_IPcam, CameraTypeEnum::IP_CAMERA);

	loadedSettings = loadSettingsFromRegistry(SCStrings::_CAM4);

	ui.cam4_Type_comboBox->setCurrentIndex(ui.cam1_Type_comboBox->findData(loadedSettings.getCameraEnumType()));
	ui.cam4_lineEdit_Name->setText(loadedSettings.getCamerName());
	ui.cam4_lineEdit_FPS->setText(QString::number(loadedSettings.getCameraFPS()));
	camSize = loadedSettings.getCameraFeedSize();
	ui.cam4_lineEdit_Width->setText(QString::number(camSize.width));
	ui.cam4_lineEdit_Height->setText(QString::number(camSize.height));
	ui.cam4_lineEdit_Connection->setText(loadedSettings.getCameraConnectionString());
	ui.cam4_checkBox_Color->setChecked(loadedSettings.getIsColor());;
}

void SettingsWindow::on_cam1_saveChanges_button_clicked()
{
	if (saveSettingsToRegistry(
		SCStrings::_CAM1,
		ui.cam1_Type_comboBox->currentData(),
		ui.cam1_lineEdit_Name->text(),
		ui.cam1_lineEdit_FPS->text().toInt(),
		ui.cam1_lineEdit_Width->text().toInt(),
		ui.cam1_lineEdit_Height->text().toInt(),
		ui.cam1_lineEdit_Connection->text(),
		ui.cam1_checkBox_Color->isChecked(),
		ui.cam1_Anon->isChecked()))
	{
		emit settingSaved();
		showOkDialog(this);
	}
	else
	{
		showFailedDialog(this);
	}
}

void SettingsWindow::on_cam2_saveChanges_button_clicked()
{
	if (saveSettingsToRegistry(
		SCStrings::_CAM2,
		ui.cam2_Type_comboBox->currentData(),
		ui.cam2_lineEdit_Name->text(),
		ui.cam2_lineEdit_FPS->text().toInt(),
		ui.cam2_lineEdit_Width->text().toInt(),
		ui.cam2_lineEdit_Height->text().toInt(),
		ui.cam2_lineEdit_Connection->text(),
		ui.cam2_checkBox_Color->isChecked(),
		ui.cam2_Anon->isChecked()))
	{
		emit settingSaved();
		showOkDialog(this);
	}
	else
	{
		showFailedDialog(this);
	}
}

void SettingsWindow::on_cam3_saveChanges_button_clicked()
{
	if (saveSettingsToRegistry(
		SCStrings::_CAM3,
		ui.cam3_Type_comboBox->currentData(),
		ui.cam3_lineEdit_Name->text(),
		ui.cam3_lineEdit_FPS->text().toInt(),
		ui.cam3_lineEdit_Width->text().toInt(),
		ui.cam3_lineEdit_Height->text().toInt(),
		ui.cam3_lineEdit_Connection->text(),
		ui.cam3_checkBox_Color->isChecked(),
		false))
	{
		emit settingSaved();
		showOkDialog(this);
	}
	else
	{
		showFailedDialog(this);
	}
}

void SettingsWindow::on_cam4_saveChanges_button_clicked()
{
	if (saveSettingsToRegistry(
		SCStrings::_CAM4,
		ui.cam4_Type_comboBox->currentData(),
		ui.cam4_lineEdit_Name->text(),
		ui.cam4_lineEdit_FPS->text().toInt(),
		ui.cam4_lineEdit_Width->text().toInt(),
		ui.cam4_lineEdit_Height->text().toInt(),
		ui.cam4_lineEdit_Connection->text(),
		ui.cam4_checkBox_Color->isChecked(),
		false))
	{
		emit settingSaved();
		showOkDialog(this);
	}
	else
	{
		showFailedDialog(this);
	}
}

void SettingsWindow::on_cam1_Type_comboBox_currentIndexChanged(int index)
{	
	ui.cam1_lineEdit_Connection->setValidator(index == 0 ? &intIndex : nullptr);
}
void SettingsWindow::on_cam2_Type_comboBox_currentIndexChanged(int index)
{
	ui.cam2_lineEdit_Connection->setValidator(index == 0 ? &intIndex : nullptr);
}
void SettingsWindow::on_cam3_Type_comboBox_currentIndexChanged(int index)
{
	ui.cam3_lineEdit_Connection->setValidator(index == 0 ? &intIndex : nullptr);
}
void SettingsWindow::on_cam4_Type_comboBox_currentIndexChanged(int index)
{
	ui.cam4_lineEdit_Connection->setValidator(index == 0 ? &intIndex : nullptr);
}

bool SettingsWindow::saveSettingsToRegistry(QString grpName, QVariant camType, QString name, int fps, int w, int h, QVariant camId, bool isColor, bool isEna)
{
	try
	{
		QSettings settings;
		settings.beginGroup(grpName);
		settings.setValue(SCStrings::_CAMERA_TYPE, camType);
		settings.setValue(SCStrings::_CAMERA_NAME, name);
		settings.setValue(SCStrings::_CAMERA_FPS, fps);
		settings.setValue(SCStrings::_CAMERA_FEED_SIZE_W, w);
		settings.setValue(SCStrings::_CAMERA_FEED_SIZE_H, h);
		settings.setValue(SCStrings::_CAMERA_CONNVALL, camId);
		settings.setValue(SCStrings::_CAMERA_IS_COLOR, isColor);
		settings.setValue(SCStrings::_ENA, isEna);
		settings.endGroup();

		return true;
	}
	catch (const std::exception&)
	{
		//should log or show to user, but we wont, no time left...
		return false;
	}
}


Camera loadSettingsFromRegistry(QString grpName)
{
	QSettings settings;
	Camera camera;

	settings.beginGroup(grpName);

	camera.setCameraTypeEnum(static_cast<CameraTypeEnum>(settings.value(SCStrings::_CAMERA_TYPE).toInt()));
	camera.setCameraFeedSize(settings.value(SCStrings::_CAMERA_FEED_SIZE_W).toInt(), settings.value(SCStrings::_CAMERA_FEED_SIZE_H).toInt());
	camera.setCameraFPS(settings.value(SCStrings::_CAMERA_FPS).toInt());
	camera.setCameraName(settings.value(SCStrings::_CAMERA_NAME).toString());
	camera.setCameraConnectionString(settings.value(SCStrings::_CAMERA_CONNVALL).toString());
	camera.setIsColor(settings.value(SCStrings::_CAMERA_IS_COLOR).toBool());
	camera.setIsEnabled(settings.value(SCStrings::_ENA).toBool());

	settings.endGroup();

	return camera;
}

void SettingsWindow::showOkDialog(QWidget* parent)
{
	QMessageBox::information(parent, SCStrings::_success, SCStrings::_settingsSavedSuccess, QMessageBox::Ok);
}

void SettingsWindow::showFailedDialog(QWidget* parent)
{
	QMessageBox::critical(parent, SCStrings::_error, SCStrings::_settingsSavedFail, QMessageBox::Ok);
}