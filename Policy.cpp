#include "Policy.h"
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>

Policy::Policy(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));

	QFile file("policy.txt");
	if (file.open(QIODevice::ReadOnly)) 
	{
		QTextStream stream(&file);
		QString hour;
		QString minute;
		QString second;
		QString policy;
		hour = stream.readLine();
		ui.lineEdit->setText(hour);
		minute = stream.readLine();
		ui.lineEdit_2->setText(minute);
		second = stream.readLine();
		ui.lineEdit_3->setText(second);

		policy = stream.readLine();
		ui.comboBox->setCurrentText(policy);

		file.close();
	}
}

Policy::~Policy()
{

}

int Policy::OnBtnOK()
{
	QFile file("policy.txt");
	if (file.open(QIODevice::WriteOnly)) 
	{
		QTextStream stream(&file);
		QString hour=ui.lineEdit->text();// ±
		stream << hour<<"\n";
		QString minute = ui.lineEdit_2->text();//∑÷
		stream << minute << "\n";
		QString second = ui.lineEdit_3->text();//√Î
		stream << second << "\n";
		QString policy;
		policy = ui.comboBox->currentText();
		stream << policy << "\n";

		file.close();
	}
	QDialog::accept();
	return 0;
}

int Policy::OnBtnCancel()
{
	reject();
	return 0;
}
