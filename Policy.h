#ifndef POLICY_H
#define POLICY_H

#include <QDialog>
#include "ui_Policy.h"

class Policy : public QDialog
{
	Q_OBJECT

public:
	Policy(QWidget *parent = 0);
	~Policy();

private slots:
	int OnBtnOK();
	int OnBtnCancel();

private:
	Ui::Policy ui;
};

#endif // POLICY_H
