#ifndef CHANNELDLG_H
#define CHANNELDLG_H

#include <QDialog>
#include <QtGui>
#include "ui_ChannelDlg.h"
#include "DataSource_Channel.h"
#include "DataSource_Channel_2.h"
#include "DataSource_Channel_3.h"
#include "DataSource_Channel_4.h"

class ChannelDlg : public QDialog
{
	Q_OBJECT

public:
	ChannelDlg(QWidget *parent = 0, Qt::WindowFlags flags=0);
	~ChannelDlg();

private slots: //ÐÇ¿Õ
    int OnItemDoubleClicked1();
	int OnItemDoubleClicked2();

	int OnAdd();
	int OnDel();

	int OnAdd_1();
	int OnDel_1();

	int OnClear();

private slots: //ÌìºÏ
    int OnItemDoubleClicked3();
    int OnItemDoubleClicked4();

    int OnAdd2();
    int OnDel2();

	int OnAdd_2();
	int OnDel_2();

	int OnClear2();

private slots:
	int OnBtnOK();
	int OnBtnCancel();

private:
	void display(HuaCao& record);
	void display(HuaCaoList& records);
	void display2(HuaCao& record);
	void display2(HuaCaoList& records);

	void display3(HuaCao& record);
	void display3(HuaCaoList& records);
	void display4(HuaCao& record);
	void display4(HuaCaoList& records);

private:
	Ui::ChannelDlg ui;
public:
	DataSource_Channel m_dataSource;
	DataSource_Channel_2 m_dataSource_2;
	DataSource_Channel_3 m_dataSource_3;
	DataSource_Channel_4 m_dataSource_4;
};

#endif // CHANNELDLG_H
