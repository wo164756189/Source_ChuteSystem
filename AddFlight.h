#ifndef ADDFLIGHT_H
#define ADDFLIGHT_H

#include <QDialog>
#include "ui_AddFlight.h"
#include "Flight.h"

class AddFlight : public QDialog
{
	Q_OBJECT

public:
	AddFlight(Flight* result, QWidget *parent = 0);
	~AddFlight();

private slots:
	int OnBtnOK();
	int OnBtnCancel();

private:
	Ui::AddFlight ui;
	Flight* m_result;

public:
	//char m_type[32];
    //int m_seat;
};

#endif // ADDFLIGHT_H
