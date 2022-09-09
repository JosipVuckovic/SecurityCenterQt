#pragma once

#include <QDialog>
#include "ui_settingswindow.h"
#include "camera.h"

Camera loadSettingsFromRegistry(QString grpName);

class SettingsWindow : public QDialog, public Ui::SettingsWindowClass
{
	Q_OBJECT

public:
	SettingsWindow(QWidget* parent = nullptr);
	~SettingsWindow();
		
	bool saveSettingsToRegistry(QString grpName, QVariant camType, QString name, int fps, int w, int h, QVariant camId, bool isColor, bool isEnabled = false);
	//bool saveSettingsToRegistry(QString grpName, QVariant camType, QString name, int fps, int w, int h, QVariant camId, bool isColor, bool isEnabled);
	void  showOkDialog(QWidget* parent);
	void  showFailedDialog(QWidget* parent);
	void fillDataForForm();
signals:
	void settingSaved();

private slots:
	void on_cam1_saveChanges_button_clicked();
	void on_cam2_saveChanges_button_clicked();
	void on_cam3_saveChanges_button_clicked();
	void on_cam4_saveChanges_button_clicked();
	void on_cam1_Type_comboBox_currentIndexChanged(int index);
	void on_cam2_Type_comboBox_currentIndexChanged(int index);
	void on_cam3_Type_comboBox_currentIndexChanged(int index);
	void on_cam4_Type_comboBox_currentIndexChanged(int index);

private:
	Ui::SettingsWindowClass ui;
	QIntValidator intValResolution;
	QIntValidator intValFPS;
	QIntValidator intIndex;
};
