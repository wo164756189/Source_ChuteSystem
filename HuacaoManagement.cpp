#include "HuacaoManagement.h"
#include "ChannelDlg.h"
#include "FlightDlg.h"
#include "Policy.h"
#include "Setting.h"


HuacaoManagement::HuacaoManagement(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.btnLock, SIGNAL(clicked(bool)), this, SLOT(OnLockedClciked())); //Lock & Unlock icon

	connect(ui.btnChannel, SIGNAL(clicked(bool)), this, SLOT(OnChannelClicked()));
	connect(ui.btnFlight, SIGNAL(clicked(bool)), this, SLOT(OnFlightClicked()));
	connect(ui.btnPolicy, SIGNAL(clicked(bool)), this, SLOT(OnPolicyClicked()));
	connect(ui.btnSetting, SIGNAL(clicked(bool)), this, SLOT(OnSettingClicked()));



}

HuacaoManagement::~HuacaoManagement()
{

}
int counter = 1;
int HuacaoManagement::OnLockedClciked()
{
	if (counter == 1)
	{
		ui.btnLock->setIcon(QIcon("Resources/open.png"));
		counter = 2;
	}
	else if (counter==2)
	{
		ui.btnLock->setIcon(QIcon("Resources/lock.png"));
		counter = 1;
	}
	
	return 0;
}
int HuacaoManagement::OnChannelClicked()
{
	ChannelDlg channelDialog(this);
	int ret=channelDialog.exec();
	//if (ret == QDialog::Rejected)
	return 0;
}
int HuacaoManagement::OnFlightClicked()
{
	FlightDlg flightDialog(this);
	flightDialog.exec();
	//flightDialog.m_dataSource.load();
	return 0;
}
int HuacaoManagement::OnPolicyClicked()
{
	Policy policyDialog(this);
	policyDialog.exec();
	return 0;
}
int HuacaoManagement::OnSettingClicked()
{
	Setting settingDialog(this);
	settingDialog.exec();
	return 0;
}


