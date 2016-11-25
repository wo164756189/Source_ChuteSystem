
#include <stdio.h>
#include <string.h>
#include "DataSource_Channel_4.h"

DataSource_Channel_4::DataSource_Channel_4()
{

}

DataSource_Channel_4::~DataSource_Channel_4()
{

}


// ����
int DataSource_Channel_4::load()
{
	FILE* fp = fopen("channel_4.txt", "rb");
	if (!fp) return 0;

	m_records.clear(); // ���

	// ��������	
	while (!feof(fp))
	{
		HuaCao record;
		int n = fread(&record, 1, sizeof(HuaCao), fp);
		if (n < 0) break;
		if (n == 0) continue;

		m_records.push_back(record);
	}

	fclose(fp);
	return 0;
}

// ����
int DataSource_Channel_4::save()
{
	FILE* fp = fopen("channel_4.txt", "wb");
	if (!fp) return -1;

	// ����ÿ����¼
	for (HuaCaoList::iterator iter = m_records.begin();
		iter != m_records.end(); iter++)
	{
		HuaCao& record = *iter;
		fwrite(&record, 1, sizeof(HuaCao), fp);
	}

	fclose(fp);
	return 0;
}

// ���
int DataSource_Channel_4::add(const HuaCao& huacao)
{
	m_records.push_back(huacao);
	return 0;
}

// ɾ��
void DataSource_Channel_4::remove(const char* HuacaoNum)
{
	for (HuaCaoList::iterator iter = m_records.begin();
		iter != m_records.end(); iter++)
	{
		HuaCao& record = *iter;
		if (strstr(record.number, HuacaoNum))   //???????
		{
			m_records.erase(iter);
			break;
		}
	}
}





