#ifndef DATASOURCE_CHANNEL_3_H
#define DATASOURCE_CHANNEL_3_H

#include "HuaCao.h"

class DataSource_Channel_3
{
public:
	DataSource_Channel_3();
	~DataSource_Channel_3();

public:
	// 加载
	int load();

	// 保存
	int save();

	// 添加
	int add(const HuaCao& huacao);

	HuaCaoList& list() { return m_records; }

	// 删除
	void remove(const char* HuacaoNum);

private:
	char m_filename[256];
	HuaCaoList m_records; // 所有飞机
};

#endif


