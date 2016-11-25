#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "ui_Setting.h"

class Setting : public QDialog
{
	Q_OBJECT

public:
	Setting(QWidget *parent = 0);
	~Setting();

private slots:
	int OnBtnOK();
	int OnBtnCancel();

private:
	Ui::Setting ui;
};

#endif // SETTING_H
