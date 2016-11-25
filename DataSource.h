#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "Flight.h"

class DataSource
{
public:
	DataSource();
	~DataSource();

public:
	// 加载
	int load();

	// 保存
	int save();

	// 添加
	int add(const Flight& Fly);

	FlightList& list() { return m_records; }

	// 删除
	void remove(const char* FlightNum);

	// 按飞机号查找 
	//Flight* find(const char* FlightNum);

	// 按飞机号匹配查找
	//void match(const char* FlightNum, FlightList& results);

private:
	char m_filename[256];
	FlightList m_records; // 所有飞机
};





#endif


