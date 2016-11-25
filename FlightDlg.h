#ifndef FLIGHTDLG_H
#define FLIGHTDLG_H

#include <QDialog>
#include <QtGui>
#include "ui_FlightDlg.h"
#include "DataSource.h"


class FlightDlg : public QDialog
{
	Q_OBJECT

public:
	FlightDlg(QWidget *parent = 0, Qt::WindowFlags flags=0);
	~FlightDlg();

public:
	//void AddItem(QString type, QString seat);

private slots:
	int OnBtnOK();
	int OnBtnCancel();
	int OnBtnAdd();
	int OnBtnDel();
	int OnClear();

private:
	void display(Flight& record);
	void display(FlightList& records);

private:
	Ui::FlightDlg ui;
public:
	DataSource m_dataSource;
};

#endif // FLIGHTDLG_H
