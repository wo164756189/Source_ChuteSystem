#include "AddFlight.h"
#include "GBK.h"


AddFlight::AddFlight(Flight* result, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_result = result;
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));
	
}

AddFlight::~AddFlight()
{

}

int AddFlight::OnBtnOK()
{
	m_result->seat = ui.textSeatNumber->text().toInt();

	string text = GBK::FromUnicode(ui.textFlightType->text());
	strcpy(m_result->FlightNum, text.c_str());
	
	//this->m_type=ui.textFlightType->text();
    //this->m_seat=ui.textSeatNumber->text().toInt();

	QDialog::accept();
	return 0;
}

int AddFlight::OnBtnCancel()
{
	reject();
	return 0;
}

