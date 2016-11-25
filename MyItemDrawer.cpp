#include "MyItemDrawer.h"
#include<QPainter>

MyItemDrawer::MyItemDrawer(QObject *parent)
	: QStyledItemDelegate(parent)
{

}

MyItemDrawer::~MyItemDrawer()
{

}

QSize MyItemDrawer::sizeHint(const QStyleOptionViewItem & option,
	const QModelIndex & index) const
{
	QSize size = QStyledItemDelegate::sizeHint(option, index);
	size.setHeight(20);
	return size;
}


void MyItemDrawer::paint(QPainter *painter, 
	const QStyleOptionViewItem &option, 
	const QModelIndex &index) const
{
	QRect rect = option.rect;
	//rect.adjust(2, 2, -2, -2);

	QString type = index.data(Qt::DisplayRole).toString();
	QString seat = index.data(Qt::UserRole + 1).toString();

	//draw selected state
	if (option.state & QStyle::State_Selected)
	{
		painter->setBrush(QColor(0xCC,0xAA,0xAA));
		painter->drawRoundedRect(rect, 2, 2);
		painter->setBrush(Qt::NoBrush);
	}
	//show type
	if (1)
	{
		QRect dst = rect;
		dst.setLeft(rect.left() + 10);
		dst.setBottom(rect.top() + 20);
		painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, type);
	}
	//show seat
	if (1)
	{
		QRect dst = rect;
		dst.setLeft(rect.left() + 100);
		dst.setBottom(rect.top() + 20);
		painter->drawText(dst, Qt::AlignLeft | Qt::AlignVCenter, seat);
	}

}
