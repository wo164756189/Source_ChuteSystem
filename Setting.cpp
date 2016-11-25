#include "Setting.h"
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>


Setting::Setting(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));

	QFile file("setting.txt");
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		QString speed;
		QString load;
		speed = stream.readLine();
		ui.lineEdit->setText(speed);
		load = stream.readLine();
		ui.lineEdit_2->setText(load);

		QString display;
		QString undisplay;
		display = stream.readLine();
		if (display=="1")
		{
			ui.radioButton->setChecked(true);
		}
		undisplay = stream.readLine();
		if (undisplay=="1")
		{
			ui.radioButton_2->setChecked(true);
		}
		file.close();
	}
}

Setting::~Setting()
{

}

int Setting::OnBtnOK()
{
	QFile file("setting.txt");
	if (file.open(QIODevice::WriteOnly))
	{
		QTextStream stream(&file);
		QString speed = ui.lineEdit->text();       //线速度（m）
		stream << speed << "\n";
		QString load = ui.lineEdit_2->text();      //负载（%）
		stream << load << "\n";

		QString display;
		QString undisplay;
		if (ui.radioButton->isChecked())
		{
			display = "1";
		}
		else
		{
			display = "0";
		}
		stream << display << "\n";

		if (ui.radioButton_2->isChecked())
		{
			undisplay = "1";
		}
		else
		{
			undisplay = "0";
		}
		stream << undisplay << "\n";


		file.close();
	}
	QDialog::accept();
	return 0;
}

int Setting::OnBtnCancel()
{
	reject();
	return 0;
}