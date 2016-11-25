#ifndef ADDHUACAO_H
#define ADDHUACAO_H

#include <QDialog>
#include "ui_AddHuacao.h"
#include "HuaCao.h"

class AddHuacao : public QDialog
{
	Q_OBJECT

public:
	AddHuacao(HuaCao *result, QWidget *parent = 0);
	~AddHuacao();

private slots:
	int OnBtnOK();
	int OnBtnCancel();

private:
	Ui::AddHuacao ui;
	HuaCao* m_result;
};

#endif // ADDHUACAO_H
