#ifndef DATASOURCE_CHANNEL_4_H
#define DATASOURCE_CHANNEL_4_H

#include "HuaCao.h"

class DataSource_Channel_4
{
public:
	DataSource_Channel_4();
	~DataSource_Channel_4();

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


