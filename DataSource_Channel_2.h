#ifndef DATASOURCE_CHANNEL_2_H
#define DATASOURCE_CHANNEL_2_H

#include "HuaCao.h"

class DataSource_Channel_2
{
public:
	DataSource_Channel_2();
	~DataSource_Channel_2();

public:
	// ����
	int load();

	// ����
	int save();

	// ���
	int add(const HuaCao& huacao);

	HuaCaoList& list() { return m_records; }

	// ɾ��
	void remove(const char* HuacaoNum);

private:
	char m_filename[256];
	HuaCaoList m_records; // ���зɻ�
};

#endif


