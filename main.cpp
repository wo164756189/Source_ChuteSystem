#include "HuacaoManagement.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "PaintTimeBar.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HuacaoManagement w;

	w.show();
	return a.exec();
}
