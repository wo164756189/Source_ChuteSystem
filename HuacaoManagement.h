#ifndef HUACAOMANAGEMENT_H
#define HUACAOMANAGEMENT_H

#include <QtWidgets/QMainWindow>
#include "ui_HuacaoManagement.h"


class HuacaoManagement : public QMainWindow
{
	Q_OBJECT

public:
	HuacaoManagement(QWidget *parent = 0);
	~HuacaoManagement();
private slots:
    int OnLockedClciked();
	int OnChannelClicked();
	int OnFlightClicked();
	int OnPolicyClicked();
	int OnSettingClicked();
private:
	Ui::HuacaoManagementClass ui;
};

#endif // HUACAOMANAGEMENT_H
