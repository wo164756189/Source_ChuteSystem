#include "FlightDlg.h"
#include "AddFlight.h"
//#include <QListWidgetItem>
//#include <QTreeWidgetItem>
//#include "Flight.h"
#include "GBK.h"
//#include "MyItemDrawer.h"

FlightDlg::FlightDlg(QWidget *parent,Qt::WindowFlags flags)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.treeWidgetFlight->setColumnWidth(0, 120);
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));
	connect(ui.btnAdd, SIGNAL(clicked()), this, SLOT(OnBtnAdd()));
	connect(ui.btnDel, SIGNAL(clicked()), this, SLOT(OnBtnDel()));
	connect(ui.btnClear, SIGNAL(clicked()), this, SLOT(OnClear()));

	// ����
	m_dataSource.load();
	display(m_dataSource.list());

	//AddItem(QString::fromLocal8Bit("�ɻ��ͺ�"), QString::fromLocal8Bit("��λ��"));
	//ui.listWidgetFlight->setItemDelegate(new MyItemDrawer(ui.listWidgetFlight));
	

	 
}

FlightDlg::~FlightDlg()
{

}

int FlightDlg::OnBtnOK()
{
	m_dataSource.save();
	QDialog::accept();
	return 0;
}

int FlightDlg::OnBtnCancel()
{
	reject();
	return 0;
}

int FlightDlg::OnBtnAdd()
{
	//AddFlight flight(this);
	//int ret = flight.exec();
	Flight result;
	AddFlight dlg(&result, this);
	if (QDialog::Accepted==dlg.exec())
	{
		m_dataSource.add(result);
		m_dataSource.save();
		display(result);
		//Flight fly;
		//fly.FlightNum = flight.m_type;
		//fly.seat = flight.m_seat;

		//QTreeWidgetItem* item = new QTreeWidgetItem();
		//item->setData(0,Qt::DisplayRole, fly.FlightNum);
		//item->setData(1,Qt::UserRole + 1, fly.seat);
		//ui.treeWidgetFlight->addTopLevelItem(item);

	}

	//AddItem(flight.m_type,flight.m_seat);
	//Flight result;
	//AddFlight dlg(&result, this);
	//if (QDialog::Accepted == dlg.exec())
	//{
	//	// ����
	//	result.FlightNum = dlg.m_type;
	//	result.seat = dlg.m_seat;
	//		
	//	m_dataSource.add(result);
	//	m_dataSource.save();

	//	// ��ʾ������
	//	display(result);
	//}
	return 0;
}

int FlightDlg::OnBtnDel()
{
	//int row=ui.listWidgetFlight->currentRow();
	//if (row ==0)
	//{
		//return 0;
	//}
	//ui.listWidgetFlight->takeItem(row);
	QTreeWidgetItem* item = ui.treeWidgetFlight->currentItem();
	if (!item) return 0; // û��ѡ����

	// ȡ���к�
	QString FlightNumber = item->data(0, Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(FlightNumber);
	char name[32];
	strcpy(name, text.c_str());

	m_dataSource.remove(name);
	m_dataSource.save();

	// �ӽ�����ɾ��������ʾ
	int index = ui.treeWidgetFlight->indexOfTopLevelItem(item);
	QTreeWidgetItem* which = ui.treeWidgetFlight->takeTopLevelItem(index);
	delete which;
	return 0;
}

int FlightDlg::OnClear()
{
	fopen("local.txt", "w+");
	m_dataSource.load();
	ui.treeWidgetFlight->clear();
	return 0;
}

// ��ʾһ����¼
void FlightDlg::display(Flight& record)
{
	// ��������
	QTreeWidgetItem* item = new QTreeWidgetItem(ui.treeWidgetFlight);
	item->setText(0, GBK::ToUnicode(record.FlightNum));
	item->setText(1, QString("%1").arg(record.seat));

	// �����к�
	item->setData(0, Qt::DisplayRole, record.FlightNum);
}

// ��ʾ������¼
void FlightDlg::display(FlightList& records)
{
	for (FlightList::iterator iter = records.begin();
		iter != records.end(); iter++)
	{
		Flight& record = *iter;

		display(record);
	}
}
