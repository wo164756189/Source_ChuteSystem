#include "ChannelDlg.h"
#include "HuaCao.h"
#include "AddHuacao.h"
#include "GBK.h"
#include <QListWidgetItem>
#include <QTreeWidgetItem>

ChannelDlg::ChannelDlg(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ui.huacaoUsed->addItem("378");
	//ui.huacaoUsed->addItem("379");
	//ui.huacaoUsed->addItem("380");
	//ui.huacaoUsed->addItem("381");
	//ui.huacaoUsed->addItem("382");

	//ui.huacaoUsed2->addItem("378");
	//ui.huacaoUsed2->addItem("379");
	//ui.huacaoUsed2->addItem("380");
	//ui.huacaoUsed2->addItem("381");
	//ui.huacaoUsed2->addItem("382");

	connect(ui.huacaoUsed, SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(OnItemDoubleClicked1()));
	connect(ui.huacaoFree, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(OnItemDoubleClicked2()));

	connect(ui.btnAdd, SIGNAL(clicked()), this, SLOT(OnAdd()));
	connect(ui.btnDel, SIGNAL(clicked()), this, SLOT(OnDel()));
	connect(ui.btnAdd_1, SIGNAL(clicked()), this, SLOT(OnAdd_1()));
	connect(ui.btnDel_1, SIGNAL(clicked()), this, SLOT(OnDel_1()));
	connect(ui.btnClear, SIGNAL(clicked()), this, SLOT(OnClear()));


	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancel()));

	connect(ui.huacaoUsed2, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(OnItemDoubleClicked3()));
	connect(ui.huacaoFree2, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(OnItemDoubleClicked4()));

	connect(ui.btnAdd2, SIGNAL(clicked()), this, SLOT(OnAdd2()));
	connect(ui.btnDel2, SIGNAL(clicked()), this, SLOT(OnDel2()));
	connect(ui.btnAdd_2, SIGNAL(clicked()), this, SLOT(OnAdd_2()));
	connect(ui.btnDel_2, SIGNAL(clicked()), this, SLOT(OnDel_2()));
	connect(ui.btnClear_2, SIGNAL(clicked()), this, SLOT(OnClear2()));

	m_dataSource.load();
	m_dataSource_2.load();
	display(m_dataSource.list());
	display2(m_dataSource_2.list());

	m_dataSource_3.load();
	m_dataSource_4.load();
	display3(m_dataSource_3.list());
	display4(m_dataSource_4.list());
}

ChannelDlg::~ChannelDlg()
{

}

int ChannelDlg::OnBtnOK()
{
	// save data
	m_dataSource.save();
	QDialog::accept();
	return 0;
}

int ChannelDlg::OnBtnCancel()
{
	// exit Channel dialog
	reject();
	return 0;
}
//星空
int ChannelDlg::OnItemDoubleClicked1()
{
	QListWidgetItem* item = ui.huacaoUsed->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(name, text.c_str());
	m_dataSource.remove(name);
	m_dataSource.save();

	HuaCao result;
	strcpy(result.number, text.c_str());
	m_dataSource_2.add(result);
	m_dataSource_2.save();

	// added before
	
	int row = ui.huacaoUsed->currentRow();
	QListWidgetItem* currentItem = ui.huacaoUsed->takeItem(row);
	ui.huacaoFree->addItem(currentItem);

	return 0;
}

int ChannelDlg::OnItemDoubleClicked2()
{
	HuaCao result;
	QListWidgetItem* item = ui.huacaoFree->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(result.number, text.c_str());
	m_dataSource.add(result);
	m_dataSource.save();

	strcpy(name, text.c_str());
    m_dataSource_2.remove(name);
	m_dataSource_2.save();
	//
	int row = ui.huacaoFree->currentRow();
	QListWidgetItem* currentItem = ui.huacaoFree->takeItem(row);
	ui.huacaoUsed->addItem(currentItem);

	return 0;
}
//左→右
int ChannelDlg::OnAdd()
{
	QListWidgetItem* item = ui.huacaoUsed->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(name, text.c_str());
	m_dataSource.remove(name);
	m_dataSource.save();

	HuaCao result;
	strcpy(result.number, text.c_str());
	m_dataSource_2.add(result);
	m_dataSource_2.save();

	// added before

	int row = ui.huacaoUsed->currentRow();
	QListWidgetItem* currentItem = ui.huacaoUsed->takeItem(row);
	ui.huacaoFree->addItem(currentItem);

	return 0;
}
//右→左
int ChannelDlg::OnDel()
{	
	HuaCao result;
	QListWidgetItem* item = ui.huacaoFree->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(result.number, text.c_str());
	m_dataSource.add(result);
	m_dataSource.save();

	strcpy(name, text.c_str());
	m_dataSource_2.remove(name);
	m_dataSource_2.save();
	//
	int row = ui.huacaoFree->currentRow();
	QListWidgetItem* currentItem = ui.huacaoFree->takeItem(row);
	ui.huacaoUsed->addItem(currentItem);

	return 0;
}
// "+" button
int ChannelDlg::OnAdd_1()
{
	HuaCao result;
	AddHuacao dlg(&result, this);
	if (QDialog::Accepted == dlg.exec())
	{
		m_dataSource.add(result);
		m_dataSource.save();
		display(result);
	}
	return 0;
}
// "-" button
int ChannelDlg::OnDel_1()
{
	QListWidgetItem* item = ui.huacaoUsed->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(name, text.c_str());

	m_dataSource.remove(name);
	m_dataSource.save();
	int row = ui.huacaoUsed->currentRow();
	ui.huacaoUsed->takeItem(row);

	// 从界面中删除该条显示

	//QListWidgetItem* item = ui.huacaoUsed->currentItem();
	//int row = ui.huacaoUsed->currentRow();
	//if (!item) return 0; // 没有选中项

	// 取得行号
	//QString HuacaoNumber = item->data(Qt::DisplayRole).toString();


	//m_dataSource.remove(HuacaoNumber);
	//m_dataSource.save();

	// 从界面中删除该条显示
	//ui.huacaoUsed->takeItem(row);

	return 0;
}

int ChannelDlg::OnClear()
{
	fopen("channel_1.txt","w+");
	fopen("channel_2.txt", "w+");
	m_dataSource.load();
	m_dataSource_2.load();
	ui.huacaoUsed->clear();
	ui.huacaoFree->clear();

	return 0;
}
//天合
int ChannelDlg::OnItemDoubleClicked3()
{
	QListWidgetItem* item = ui.huacaoUsed2->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(name, text.c_str());
	m_dataSource_3.remove(name);
	m_dataSource_3.save();

	HuaCao result;
	strcpy(result.number, text.c_str());
	m_dataSource_4.add(result);
	m_dataSource_4.save();

	// added before

	int row = ui.huacaoUsed2->currentRow();
	QListWidgetItem* currentItem = ui.huacaoUsed2->takeItem(row);
	ui.huacaoFree2->addItem(currentItem);

	return 0;
}

int ChannelDlg::OnItemDoubleClicked4()
{
	HuaCao result;
	QListWidgetItem* item = ui.huacaoFree2->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(result.number, text.c_str());
	m_dataSource_3.add(result);
	m_dataSource_3.save();

	strcpy(name, text.c_str());
	m_dataSource_4.remove(name);
	m_dataSource_4.save();
	//
	int row = ui.huacaoFree2->currentRow();
	QListWidgetItem* currentItem = ui.huacaoFree2->takeItem(row);
	ui.huacaoUsed2->addItem(currentItem);

	return 0;
}

int ChannelDlg::OnAdd2()
{
	QListWidgetItem* item = ui.huacaoUsed2->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(name, text.c_str());
	m_dataSource_3.remove(name);
	m_dataSource_3.save();

	HuaCao result;
	strcpy(result.number, text.c_str());
	m_dataSource_4.add(result);
	m_dataSource_4.save();

	// added before

	int row = ui.huacaoUsed2->currentRow();
	QListWidgetItem* currentItem = ui.huacaoUsed2->takeItem(row);
	ui.huacaoFree2->addItem(currentItem);

	return 0;
}

int ChannelDlg::OnDel2()
{
	HuaCao result;
	QListWidgetItem* item = ui.huacaoFree2->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(result.number, text.c_str());
	m_dataSource_3.add(result);
	m_dataSource_3.save();

	strcpy(name, text.c_str());
	m_dataSource_4.remove(name);
	m_dataSource_4.save();
	//
	int row = ui.huacaoFree2->currentRow();
	QListWidgetItem* currentItem = ui.huacaoFree2->takeItem(row);
	ui.huacaoUsed2->addItem(currentItem);

	return 0;
}

int ChannelDlg::OnAdd_2()
{
	HuaCao result;
	AddHuacao dlg(&result, this);
	if (QDialog::Accepted == dlg.exec())
	{
		m_dataSource_3.add(result);
		m_dataSource_3.save();
		display3(result);
	}
	return 0;
}
int ChannelDlg::OnDel_2()
{
	QListWidgetItem* item = ui.huacaoUsed2->currentItem();
	if (!item) return 0; // 没有选中项

	// 取得行号
	QString HuacaoNumber = item->data(Qt::DisplayRole).toString();
	string text = GBK::FromUnicode(HuacaoNumber);
	char name[32];
	strcpy(name, text.c_str());

	m_dataSource_3.remove(name);
	m_dataSource_3.save();
	int row = ui.huacaoUsed2->currentRow();
	ui.huacaoUsed2->takeItem(row);

	return 0;
}
int ChannelDlg::OnClear2()
{
	//
	fopen("channel_3.txt", "w+");
	fopen("channel_4.txt", "w+");
	m_dataSource_3.load();
	m_dataSource_4.load();
	ui.huacaoUsed2->clear();
	ui.huacaoFree2->clear();

	return 0;
}

// 显示一条记录
void ChannelDlg::display(HuaCao& record)
{
	// 设置数据
	QListWidgetItem* item = new QListWidgetItem(ui.huacaoUsed);
	item->setText(record.number);

}

// 显示多条记录
void ChannelDlg::display(HuaCaoList& records)
{
	for (HuaCaoList::iterator iter = records.begin();
		iter != records.end(); iter++)
	{
		HuaCao& record = *iter;

		display(record);
	}
}

void ChannelDlg::display2(HuaCao& record)
{
	// 设置数据
	QListWidgetItem* item = new QListWidgetItem(ui.huacaoFree);
	item->setText(record.number);
}

void ChannelDlg::display2(HuaCaoList& records)
{
	for (HuaCaoList::iterator iter = records.begin();
		iter != records.end(); iter++)
	{
		HuaCao& record = *iter;

		display2(record);
	}
}

// 显示一条记录
void ChannelDlg::display3(HuaCao& record)
{
	// 设置数据
	QListWidgetItem* item = new QListWidgetItem(ui.huacaoUsed2);
	item->setText(record.number);

}

// 显示多条记录
void ChannelDlg::display3(HuaCaoList& records)
{
	for (HuaCaoList::iterator iter = records.begin();
		iter != records.end(); iter++)
	{
		HuaCao& record = *iter;

		display3(record);
	}
}

void ChannelDlg::display4(HuaCao& record)
{
	// 设置数据
	QListWidgetItem* item = new QListWidgetItem(ui.huacaoFree2);
	item->setText(record.number);
}

void ChannelDlg::display4(HuaCaoList& records)
{
	for (HuaCaoList::iterator iter = records.begin();
		iter != records.end(); iter++)
	{
		HuaCao& record = *iter;

		display4(record);
	}
}