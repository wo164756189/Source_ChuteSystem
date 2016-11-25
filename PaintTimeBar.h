#ifndef PAINTTIMEBAR_H
#define PAINTTIMEBAR_H

#include <QFrame>


class PaintTimeBar : public QWidget
{
	Q_OBJECT

public:
	PaintTimeBar(QWidget *parent, Qt::WindowFlags flags = 0);
	PaintTimeBar();
	~PaintTimeBar();
signals:
	void focused(bool yes);

private:
	// event
	virtual void paintEvent(QPaintEvent * event);
	virtual void mousePressEvent(QMouseEvent* event);

private:
	bool m_pressed;
};

#endif // PAINTTIMEBAR_H
