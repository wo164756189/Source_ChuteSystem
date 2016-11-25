
#include <stdio.h>
#include <string.h>
#include "DataSource.h"

DataSource::DataSource()
{

}

DataSource::~DataSource()
{

}


// ����
int DataSource::load()
{
	FILE* fp = fopen("local.txt", "rb");
	if (!fp) return 0;

	m_records.clear(); // ���

	// ��������	
	while (!feof(fp))
	{
		Flight record;
		int n = fread(&record, 1, sizeof(Flight), fp);
		if (n < 0) break;
		if (n == 0) continue;

		m_records.push_back(record);
	}

	fclose(fp);
	return 0;
}

// ����
int DataSource::save()
{
	FILE* fp = fopen("local.txt", "wb");
	if (!fp) return -1;

	// ����ÿ����¼
	for (FlightList::iterator iter = m_records.begin();
		iter != m_records.end(); iter++)
	{
		Flight& record = *iter;
		fwrite(&record, 1, sizeof(Flight), fp);
	}

	fclose(fp);
	return 0;
}

// ���
int DataSource::add(const Flight& fly)
{
	m_records.push_back(fly);
	return 0;
}

// ɾ��
void DataSource::remove(const char* FlightNum)
{
	for (FlightList::iterator iter = m_records.begin();
		iter != m_records.end(); iter++)
	{
		Flight& record = *iter;
		if (strstr(record.FlightNum,FlightNum))   //???????
		{
			m_records.erase(iter);
			break;
		}
	}
}

// ��ѧ�Ų��� 
//Flight* DataSource::find(const char* FlightNum)
//{
//	for (FlightList::iterator iter = m_records.begin();
//		iter != m_records.end(); iter++)
//	{
//		Flight& record = *iter;
//		if (strstr(record.FlightNum, FlightNum) != NULL)
//		{
//			return &record;
//		}
//	}
//	return NULL;
//}

// ������ƥ�����
//void DataSource::match(const char* FlightNum, FlightList& results)
//{
//	for (FlightList::iterator iter = m_records.begin();
//		iter != m_records.end(); iter++)
//	{
//		Flight& record = *iter;
//		// ��׼C��Ĳ��Һ���
//		if (strstr(record.FlightNum, FlightNum) != NULL)
//		{
//			results.push_back(record);
//		}
//	}
//}




