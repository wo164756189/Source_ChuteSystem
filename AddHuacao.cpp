#include "AddHuacao.h"
#include "GBK.h"

AddHuacao::AddHuacao(HuaCao *result, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_result = result;
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));
}

AddHuacao::~AddHuacao()
{

}

int AddHuacao::OnBtnOK()
{
	//m_result->number = ui.textHuacaoNumber->text();

	string text = GBK::FromUnicode(ui.textHuacaoNumber->text());
	strcpy(m_result->number, text.c_str());

	//this->m_type=ui.textFlightType->text();
	//this->m_seat=ui.textSeatNumber->text().toInt();

	QDialog::accept();
	return 0;
}

int AddHuacao::OnBtnCancel()
{
	reject();
	return 0;
}