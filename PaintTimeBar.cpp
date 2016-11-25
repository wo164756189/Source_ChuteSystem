#include "PaintTimeBar.h"
#include <QPainter>
#include "GBK.h"
#include <assert.h>
#include <vector>
#include <QMouseEvent>
#include <QTextCursor>
#include <QToolTip>
#include <string>
#include <QDebug>
#include <QLabel>
#include <QApplication>

using namespace std;
#define FACTOR 5.0    //  Used for define gray level
#define LENGTH 42     //  length of first time bar
#define WIDTH 10      //  width of each time bar
#define HEIGHT 20     //  height of each time interval
#define START_X 300   //  start position of x
#define START_Y 80    //  start position of y
#define SPACING 240   //  interval of adjacent time bar
#define WORDWIDTH 40  //  word length of "flight name" text

// Flight types
#define TYPE1 180
#define TYPE2 220
#define TYPE3 380
#define TYPE4 500


class FlightInfo
{
public:
	FlightInfo(){}
	FlightInfo(int checkIn_h, int checkIn_m, int depatureTime_h, int depatureTime_m, int time, QString flight, QString type, int seat)
	{
		this->checkIn_h = checkIn_h;
		this->checkIn_m = checkIn_m;
		this->depatureTime_h = depatureTime_h;
		this->depatureTime_m = depatureTime_m;
		this->time = time;
		this->flight = flight;
		this->type = type;
		this->seat = seat;
	}
	~FlightInfo()
	{

	}
public:
	//float checkIn;
	//float depatureTime;
	int checkIn_h;
	int checkIn_m;
	int depatureTime_h;
	int depatureTime_m;
	int time;  // depatureTime 向下取整
	QString flight;
	QString type;
	int seat;
};

// define global parameters for each Chute
vector<FlightInfo> FlightList_1;
vector<FlightInfo> FlightList_2;
vector<FlightInfo> FlightList_3;
vector<FlightInfo> FlightList_4;

// mapping the seat number to density gray level
void getGrayLevel(float * DensityForEachHour,int * GrayLevel)
{
	for (int i = 0; i < 24; i++ )
	{
		if (DensityForEachHour[i] * 255>=255.0)
		{
			GrayLevel[i] = 0;
		}
		else
		{
			GrayLevel[i] = 255 - floor(DensityForEachHour[i] * 255);
		}
		
	}
}

PaintTimeBar::PaintTimeBar(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent)
{

}

PaintTimeBar::PaintTimeBar()
{
	char buf_1[128];  //buffer for each line in config_channel.txt
	char buf_2[128];
	char buf_3[128];
	char buf_4[128];
	///////////////////////////////////    bar 1    ////////////////////////////////////////
	FILE* fp1 = fopen("Source_ChuteSystem/config_channel_1.txt", "rb");
	while (!feof(fp1))
	{
		char* line = fgets(buf_1, 128, fp1);
		if (line)
		{
			int check_h, check_m, depature_h, depature_m, time, seat;
			char flight[256];
			char type[256];
			sscanf(line, "%d:%d,%d:%d,%[^,],%s", &check_h,&check_m,&depature_h,&depature_m,flight,type);//analysis

			// get the number of seats by "type"
			time = depature_h;
			if (strcmp(type, "type1") == 0)
			{
				seat = TYPE1;
			}
			else if (strcmp(type, "type2") == 0)
			{
				seat = TYPE2;
			}
			else if (strcmp(type, "type3") == 0)
			{
				seat = TYPE3;
			}
			else
			{
				seat = TYPE4;
			}

			FlightInfo temp(check_h, check_m, depature_h, depature_m, time, QString(flight), QString(type), seat);
			FlightList_1.push_back(temp);
		}
	}

	int num_1[24] = { 0 };

	for (vector<FlightInfo>::iterator iter = FlightList_1.begin(); iter != FlightList_1.end(); iter++)
	{
		QLabel *lbl = new QLabel(this);
		QFont lbl_font;
		lbl_font.setPointSize(7);      
		lbl->setFont(lbl_font);
		lbl->setText(iter->flight);
		lbl->adjustSize();

		num_1[iter->time]++;
		lbl->setGeometry(QRect(START_X + 2 * WIDTH + 0 * (WIDTH + SPACING) +(num_1[iter->time]-1)*WORDWIDTH, START_Y + (iter->time+0.25) * HEIGHT, lbl->width(), lbl->height())); //设置大小和位置  
				
		char text[128];
		sprintf(text, "From %.2d:%.2d to %.2d:%.2d", iter->checkIn_h, iter->checkIn_m, iter->depatureTime_h, iter->depatureTime_m);
		lbl->setToolTip(QString(text));
		
	}
	///////////////////////////////////    bar 2    ///////////////////////////////////////
	FILE* fp2 = fopen("Source_ChuteSystem/config_channel_2.txt", "rb");
	while (!feof(fp2))
	{
		char* line = fgets(buf_2, 128, fp2);
		if (line)
		{
			int check_h, check_m, depature_h, depature_m, time, seat;
			char flight[256];
			char type[256];
			sscanf(line, "%d:%d,%d:%d,%[^,],%s", &check_h, &check_m, &depature_h, &depature_m, flight, type);//analysis

			// get the number of seats by "type"
			time = depature_h;
			if (strcmp(type, "type1") == 0)
			{
				seat = TYPE1;
			}
			else if (strcmp(type, "type2") == 0)
			{
				seat = TYPE2;
			}
			else if (strcmp(type, "type3") == 0)
			{
				seat = TYPE3;
			}
			else
			{
				seat = TYPE4;
			}

			FlightInfo temp(check_h, check_m, depature_h, depature_m, time, QString(flight), QString(type), seat);
			FlightList_2.push_back(temp);
		}
	}

	int num_2[24] = { 0 };

	for (vector<FlightInfo>::iterator iter = FlightList_2.begin(); iter != FlightList_2.end(); iter++)
	{
		QLabel *lbl = new QLabel(this);
		QFont lbl_font;
		lbl_font.setPointSize(7);
		lbl->setFont(lbl_font);
		lbl->setText(iter->flight);
		lbl->adjustSize();

		num_2[iter->time]++;
		lbl->setGeometry(QRect(START_X + 2 * WIDTH + 1 * (WIDTH + SPACING) + (num_2[iter->time] - 1)*WORDWIDTH, START_Y + (iter->time + 0.25) * HEIGHT, lbl->width(), lbl->height())); //设置大小和位置  

		char text[128];
		sprintf(text, "From %.2d:%.2d to %.2d:%.2d", iter->checkIn_h, iter->checkIn_m, iter->depatureTime_h, iter->depatureTime_m);
		lbl->setToolTip(QString(text));
	}
	///////////////////////////////////    bar 3    ////////////////////////////////////////
	FILE* fp3 = fopen("Source_ChuteSystem/config_channel_3.txt", "rb");
	while (!feof(fp3))
	{
		char* line = fgets(buf_3, 128, fp3);
		if (line)
		{
			int check_h, check_m, depature_h, depature_m, time, seat;
			char flight[256];
			char type[256];
			sscanf(line, "%d:%d,%d:%d,%[^,],%s", &check_h, &check_m, &depature_h, &depature_m, flight, type);//analysis

			// get the number of seats by "type"
			time = depature_h;
			if (strcmp(type, "type1") == 0)
			{
				seat = TYPE1;
			}
			else if (strcmp(type, "type2") == 0)
			{
				seat = TYPE2;
			}
			else if (strcmp(type, "type3") == 0)
			{
				seat = TYPE3;
			}
			else
			{
				seat = TYPE4;
			}

			FlightInfo temp(check_h, check_m, depature_h, depature_m, time, QString(flight), QString(type), seat);
			FlightList_3.push_back(temp);
		}
	}

	int num_3[24] = { 0 };

	for (vector<FlightInfo>::iterator iter = FlightList_3.begin(); iter != FlightList_3.end(); iter++)
	{
		QLabel *lbl = new QLabel(this);
		QFont lbl_font;
		lbl_font.setPointSize(7);
		lbl->setFont(lbl_font);
		lbl->setText(iter->flight);
		lbl->adjustSize();

		num_3[iter->time]++;
		lbl->setGeometry(QRect(START_X + 2 * WIDTH + 2 * (WIDTH + SPACING) + (num_3[iter->time] - 1)*WORDWIDTH, START_Y + (iter->time + 0.25) * HEIGHT, lbl->width(), lbl->height())); //设置大小和位置  

		char text[128];
		sprintf(text, "From %.2d:%.2d to %.2d:%.2d", iter->checkIn_h, iter->checkIn_m, iter->depatureTime_h, iter->depatureTime_m);
		lbl->setToolTip(QString(text));
	}
	///////////////////////////////////    bar 4    ////////////////////////////////////////
	FILE* fp4 = fopen("Source_ChuteSystem/config_channel_4.txt", "rb");
	while (!feof(fp4))
	{
		char* line = fgets(buf_4, 128, fp4);
		if (line)
		{
			int check_h, check_m, depature_h, depature_m, time, seat;
			char flight[256];
			char type[256];
			sscanf(line, "%d:%d,%d:%d,%[^,],%s", &check_h, &check_m, &depature_h, &depature_m, flight, type);//analysis

			// get the number of seats by "type"
			time = depature_h;
			if (strcmp(type, "type1") == 0)
			{
				seat = TYPE1;
			}
			else if (strcmp(type, "type2") == 0)
			{
				seat = TYPE2;
			}
			else if (strcmp(type, "type3") == 0)
			{
				seat = TYPE3;
			}
			else
			{
				seat = TYPE4;
			}

			FlightInfo temp(check_h, check_m, depature_h, depature_m, time, QString(flight), QString(type), seat);
			FlightList_4.push_back(temp);
		}
	}
	int num_4[24] = { 0 };

	for (vector<FlightInfo>::iterator iter = FlightList_4.begin(); iter != FlightList_4.end(); iter++)
	{
		QLabel *lbl = new QLabel(this);
		QFont lbl_font;
		lbl_font.setPointSize(7);
		lbl->setFont(lbl_font);
		lbl->setText(iter->flight);
		lbl->adjustSize();

		num_4[iter->time]++;
		lbl->setGeometry(QRect(START_X + 2 * WIDTH + 3 * (WIDTH + SPACING) + (num_4[iter->time] - 1)*WORDWIDTH, START_Y + (iter->time + 0.25) * HEIGHT, lbl->width(), lbl->height())); //设置大小和位置  

		char text[128];
		sprintf(text, "From %.2d:%.2d to %.2d:%.2d", iter->checkIn_h, iter->checkIn_m, iter->depatureTime_h, iter->depatureTime_m);
		lbl->setToolTip(QString(text));
	}
}

PaintTimeBar::~PaintTimeBar()
{

}

void PaintTimeBar::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	// draw the timeBar
	painter.setPen(QPen(QColor(180, 180, 180)));
	painter.drawRect(100, 80, LENGTH, HEIGHT * 24);
	// draw the time
	painter.setPen(QPen(QColor(60, 60, 60)));
	QFont Font("Times", 10, QFont::Bold);
	painter.drawText(100, 80, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("00:00"));
	painter.drawText(100, 80 + 3 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("03:00"));
	painter.drawText(100, 80 + 6 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("06:00"));
	painter.drawText(100, 80 + 9 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("09:00"));
	painter.drawText(100, 80 + 12 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("12:00"));
	painter.drawText(100, 80 + 15 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("15:00"));
	painter.drawText(100, 80 + 18 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("18:00"));
	painter.drawText(100, 80 + 21 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("21:00"));
	painter.drawText(100, 80 + 23 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("23:59"));

	// define global parameters
	//vector<FlightInfo> FlightList_1;
	int seat_time_1[24] = { 0 };
	float Density_1[24];
	int seat_sum_1 = 0;
	//char buf_1[128];  //buffer for each line in config_channel.txt
	int GrayLevel_1[24];
	QColor color_channel_1[24];
	QString flightInfo_1[24];

	//vector<FlightInfo> FlightList_2;
	int seat_time_2[24] = { 0 };
	float Density_2[24];
	int seat_sum_2 = 0;
	//char buf_2[128];  
	int GrayLevel_2[24];
	QColor color_channel_2[24];
	QString flightInfo_2[24];

	//vector<FlightInfo> FlightList_3;
	int seat_time_3[24] = { 0 };
	float Density_3[24];
	int seat_sum_3 = 0;
	//char buf_3[128];
	int GrayLevel_3[24];
	QColor color_channel_3[24];
	QString flightInfo_3[24];

	//vector<FlightInfo> FlightList_4;
	int seat_time_4[24] = { 0 };
	float Density_4[24];
	int seat_sum_4 = 0;
	//char buf_4[128];
	int GrayLevel_4[24];
	QColor color_channel_4[24];
	QString flightInfo_4[24];

	////////////////////////////// bar 1//////////////////////////////
	painter.setPen(QPen(QColor(60, 60, 60)));
	painter.drawText(START_X - LENGTH, 80, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("00:00"));
	painter.drawText(START_X - LENGTH, 80 + 3 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("03:00"));
	painter.drawText(START_X - LENGTH, 80 + 6 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("06:00"));
	painter.drawText(START_X - LENGTH, 80 + 9 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("09:00"));
	painter.drawText(START_X - LENGTH, 80 + 12 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("12:00"));
	painter.drawText(START_X - LENGTH, 80 + 15 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("15:00"));
	painter.drawText(START_X - LENGTH, 80 + 18 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("18:00"));
	painter.drawText(START_X - LENGTH, 80 + 21 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("21:00"));
	painter.drawText(START_X - LENGTH, 80 + 23 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("23:59"));

	for (vector<FlightInfo>::iterator iter = FlightList_1.begin(); iter != FlightList_1.end(); iter++)
	{
		seat_sum_1 = seat_sum_1 + iter->seat;
	}


	for (vector<FlightInfo>::iterator iter = FlightList_1.begin(); iter != FlightList_1.end(); iter++)
	{
		seat_time_1[iter->time] = seat_time_1[iter->time] + iter->seat;
		for (int i = 0; i < 24; i++)
		{
			Density_1[i] = seat_time_1[i] * FACTOR / seat_sum_1;
		}
	}

	getGrayLevel(Density_1, GrayLevel_1);

	for (int i = 0; i < 24; i++)
	{
		color_channel_1[i].setRgb(GrayLevel_1[i], GrayLevel_1[i], GrayLevel_1[i]);
	}

	for (int i = 0; i < 24; i++)
	{
		painter.setBrush(QBrush(color_channel_1[i]));
		painter.setPen(QPen(color_channel_1[i]));
		painter.drawRect(START_X, START_Y + i*HEIGHT, WIDTH, HEIGHT);
	}
	// draw the bounding box
	painter.setPen(QPen(QColor(180, 180, 180)));
	painter.drawLine(QLine(START_X, START_Y, START_X + WIDTH, START_Y));  //top line
	painter.drawLine(QLine(START_X, START_Y, START_X, START_Y + 24 * HEIGHT));  //left line
	painter.drawLine(QLine(START_X + WIDTH, START_Y, START_X + WIDTH, START_Y + 24 * HEIGHT));  //right line
	painter.drawLine(QLine(START_X, START_Y + 24 * HEIGHT, START_X + WIDTH, START_Y + 24 * HEIGHT));  //bottom line

	////////////////////////////// bar 2//////////////////////////////
	painter.setPen(QPen(QColor(60, 60, 60)));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("00:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 3 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("03:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 6 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("06:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 9 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("09:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 12 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("12:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 15 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("15:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 18 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("18:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 21 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("21:00"));
	painter.drawText(START_X - LENGTH + 1 * (WIDTH + SPACING), 80 + 23 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("23:59"));

	for (vector<FlightInfo>::iterator iter = FlightList_2.begin(); iter != FlightList_2.end(); iter++)
	{
		seat_sum_2 = seat_sum_2 + iter->seat;
	}


	for (vector<FlightInfo>::iterator iter = FlightList_2.begin(); iter != FlightList_2.end(); iter++)
	{
		seat_time_2[iter->time] = seat_time_2[iter->time] + iter->seat;
		for (int i = 0; i < 24; i++)
		{
			Density_2[i] = seat_time_2[i] * FACTOR / seat_sum_2;
		}
	}

	getGrayLevel(Density_2, GrayLevel_2);

	for (int i = 0; i < 24; i++)
	{
		color_channel_2[i].setRgb(GrayLevel_2[i], GrayLevel_2[i], GrayLevel_2[i]);
	}

	for (int i = 0; i < 24; i++)
	{
		painter.setBrush(QBrush(color_channel_2[i]));
		painter.setPen(QPen(color_channel_2[i]));
		painter.drawRect(START_X + 1 * (SPACING + WIDTH), START_Y + i*HEIGHT, WIDTH, HEIGHT);
	}
	// draw the bounding box
	painter.setPen(QPen(QColor(180, 180, 180)));
	painter.drawLine(QLine(START_X + 1 * (SPACING + WIDTH), START_Y, START_X + WIDTH + 1 * (SPACING + WIDTH), START_Y));  //top line
	painter.drawLine(QLine(START_X + 1 * (SPACING + WIDTH), START_Y, START_X + 1 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //left line
	painter.drawLine(QLine(START_X + WIDTH + 1 * (SPACING + WIDTH), START_Y, START_X + WIDTH + 1 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //right line
	painter.drawLine(QLine(START_X + 1 * (SPACING + WIDTH), START_Y + 24 * HEIGHT, START_X + WIDTH + 1 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //bottom line

	////////////////////////////// bar 3//////////////////////////////
	painter.setPen(QPen(QColor(60, 60, 60)));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("00:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 3 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("03:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 6 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("06:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 9 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("09:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 12 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("12:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 15 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("15:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 18 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("18:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 21 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("21:00"));
	painter.drawText(START_X - LENGTH + 2 * (WIDTH + SPACING), 80 + 23 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("23:59"));

	for (vector<FlightInfo>::iterator iter = FlightList_3.begin(); iter != FlightList_3.end(); iter++)
	{
		seat_sum_3 = seat_sum_3 + iter->seat;
	}


	for (vector<FlightInfo>::iterator iter = FlightList_3.begin(); iter != FlightList_3.end(); iter++)
	{
		seat_time_3[iter->time] = seat_time_3[iter->time] + iter->seat;
		for (int i = 0; i < 24; i++)
		{
			Density_3[i] = seat_time_3[i] * FACTOR / seat_sum_3;
		}
	}

	getGrayLevel(Density_3, GrayLevel_3);

	for (int i = 0; i < 24; i++)
	{
		color_channel_3[i].setRgb(GrayLevel_3[i], GrayLevel_3[i], GrayLevel_3[i]);
	}

	for (int i = 0; i < 24; i++)
	{
		painter.setBrush(QBrush(color_channel_3[i]));
		painter.setPen(QPen(color_channel_3[i]));
		painter.drawRect(START_X + 2 * (SPACING + WIDTH), START_Y + i*HEIGHT, WIDTH, HEIGHT);
	}
	// draw the bounding box
	painter.setPen(QPen(QColor(180, 180, 180)));
	painter.drawLine(QLine(START_X + 2 * (SPACING + WIDTH), START_Y, START_X + WIDTH + 2 * (SPACING + WIDTH), START_Y));  //top line
	painter.drawLine(QLine(START_X + 2 * (SPACING + WIDTH), START_Y, START_X + 2 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //left line
	painter.drawLine(QLine(START_X + WIDTH + 2 * (SPACING + WIDTH), START_Y, START_X + WIDTH + 2 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //right line
	painter.drawLine(QLine(START_X + 2 * (SPACING + WIDTH), START_Y + 24 * HEIGHT, START_X + WIDTH + 2 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //bottom line

	////////////////////////////// bar 4//////////////////////////////
	painter.setPen(QPen(QColor(60, 60, 60)));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("00:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 3 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("03:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 6 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("06:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 9 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("09:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 12 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("12:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 15 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("15:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 18 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("18:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 21 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("21:00"));
	painter.drawText(START_X - LENGTH + 3 * (WIDTH + SPACING), 80 + 23 * HEIGHT, LENGTH, HEIGHT, Qt::AlignHCenter | Qt::AlignVCenter, GBK::ToUnicode("23:59"));

	for (vector<FlightInfo>::iterator iter = FlightList_4.begin(); iter != FlightList_4.end(); iter++)
	{
		seat_sum_4 = seat_sum_4 + iter->seat;
	}


	for (vector<FlightInfo>::iterator iter = FlightList_4.begin(); iter != FlightList_4.end(); iter++)
	{

		seat_time_4[iter->time] = seat_time_4[iter->time] + iter->seat;
		for (int i = 0; i < 24; i++)
		{
			Density_4[i] = seat_time_4[i] * FACTOR / seat_sum_4;
		}
	}

	getGrayLevel(Density_4, GrayLevel_4);

	for (int i = 0; i < 24; i++)
	{
		color_channel_4[i].setRgb(GrayLevel_4[i], GrayLevel_4[i], GrayLevel_4[i]);
	}

	for (int i = 0; i < 24; i++)
	{
		painter.setBrush(QBrush(color_channel_4[i]));
		painter.setPen(QPen(color_channel_4[i]));
		painter.drawRect(START_X + 3 * (SPACING + WIDTH), START_Y + i*HEIGHT, WIDTH, HEIGHT);
	}
	// draw the bounding box
	painter.setPen(QPen(QColor(180, 180, 180)));
	painter.drawLine(QLine(START_X + 3 * (SPACING + WIDTH), START_Y, START_X + WIDTH + 3 * (SPACING + WIDTH), START_Y));  //top line
	painter.drawLine(QLine(START_X + 3 * (SPACING + WIDTH), START_Y, START_X + 3 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //left line
	painter.drawLine(QLine(START_X + WIDTH + 3 * (SPACING + WIDTH), START_Y, START_X + WIDTH + 3 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //right line
	painter.drawLine(QLine(START_X + 3 * (SPACING + WIDTH), START_Y + 24 * HEIGHT, START_X + WIDTH + 3 * (SPACING + WIDTH), START_Y + 24 * HEIGHT));  //bottom line

	QWidget::paintEvent(event);
}

void PaintTimeBar::mousePressEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	if (event->button() == Qt::LeftButton)
	{
		m_pressed = true;
	}
	/////////////bar 1////////////////
	if (pos.x() > START_X && pos.x() < (START_X + WIDTH) && pos.y() > START_Y && pos.y() < (START_Y + 24 * HEIGHT) && m_pressed)
	{
		int time=(pos.y() - 80) / 20;		
		QString Str = QString::number(time) + ":00~" + QString::number(time + 1) + ":00";
		QToolTip::showText(mapToGlobal(event->pos()), Str);	
	}
	/////////////bar 2////////////////
	if (pos.x() > (START_X + 1 * (SPACING + WIDTH)) && pos.x() < (START_X + WIDTH + 1 * (SPACING + WIDTH)) && pos.y() > START_Y && pos.y() < (START_Y + 24 * HEIGHT) && m_pressed)
	{
		int time = (pos.y() - 80) / 20;
		QString Str = QString::number(time) + ":00~" + QString::number(time + 1) + ":00";
		QToolTip::showText(mapToGlobal(event->pos()), Str);
	}
	/////////////bar 3////////////////
	if (pos.x() > (START_X + 2 * (SPACING + WIDTH)) && pos.x() < (START_X + WIDTH + 2 * (SPACING + WIDTH)) && pos.y() > START_Y && pos.y() < (START_Y + 24 * HEIGHT) && m_pressed)
	{
		int time = (pos.y() - 80) / 20;
		QString Str = QString::number(time) + ":00~" + QString::number(time + 1) + ":00";
		QToolTip::showText(mapToGlobal(event->pos()), Str);
	}
	/////////////bar 3////////////////
	if (pos.x() > (START_X + 3 * (SPACING + WIDTH)) && pos.x() < (START_X + WIDTH + 3 * (SPACING + WIDTH)) && pos.y() > START_Y && pos.y() < (START_Y + 24 * HEIGHT) && m_pressed)
	{
		int time = (pos.y() - 80) / 20;
		QString Str = QString::number(time) + ":00~" + QString::number(time + 1) + ":00";
		QToolTip::showText(mapToGlobal(event->pos()), Str);
	}
	//QWidget::mousePressEvent(event);

	//int mouse_x = event->pos.x();   //鼠标点击处横坐标
	//int mouse_y = event->pos.y();   //鼠标点击处纵坐标
	//QWidget *action = QApplication::widgetAt(mouse_x, mouse_y);//获取鼠标点击处的控件
	//QPoint GlobalPoint(action->mapToGlobal(QPoint(0, 0)));//获取该控件在窗体中的坐标
    //浮动显示鼠标位置的代码
	//QString pStr("%1,%2");
	//pStr = pStr.arg(event->pos().x()).arg(event->pos().y());
	//QToolTip::showText(mapToGlobal(event->pos()), pStr);
}



