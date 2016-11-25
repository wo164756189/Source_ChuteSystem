#ifndef MYITEMDRAWER_H
#define MYITEMDRAWER_H

#include <QStyledItemDelegate>

class MyItemDrawer : public QStyledItemDelegate
{
	Q_OBJECT

public:
	MyItemDrawer(QObject *parent);
	~MyItemDrawer();

private:
		//determine the block size
	virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
	    //determine how to draw
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // MYITEMDRAWER_H
