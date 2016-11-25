#ifndef DATASOURCE_CHANNEL_H
#define DATASOURCE_CHANNEL_H

#include "HuaCao.h"

class DataSource_Channel
{
public:
	DataSource_Channel();
	~DataSource_Channel();

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


