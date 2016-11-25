
#include <stdio.h>
#include <string.h>
#include "DataSource_Channel.h"

DataSource_Channel::DataSource_Channel()
{

}

DataSource_Channel::~DataSource_Channel()
{

}


// 加载
int DataSource_Channel::load()
{
	FILE* fp = fopen("channel_1.txt", "rb");
	if (!fp) return 0;

	m_records.clear(); // 清空

	// 加载数据	
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

// 保存
int DataSource_Channel::save()
{
	FILE* fp = fopen("channel_1.txt", "wb");
	if (!fp) return -1;

	// 保存每条记录
	for (HuaCaoList::iterator iter = m_records.begin();
		iter != m_records.end(); iter++)
	{
		HuaCao& record = *iter;
		fwrite(&record, 1, sizeof(HuaCao), fp);
	}

	fclose(fp);
	return 0;
}

// 添加
int DataSource_Channel::add(const HuaCao& huacao)
{
	m_records.push_back(huacao);
	return 0;
}

// 删除
void DataSource_Channel::remove(const char* HuacaoNum)
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

// 按学号查找 
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

// 按姓名匹配查找
//void DataSource::match(const char* FlightNum, FlightList& results)
//{
//	for (FlightList::iterator iter = m_records.begin();
//		iter != m_records.end(); iter++)
//	{
//		Flight& record = *iter;
//		// 标准C里的查找函数
//		if (strstr(record.FlightNum, FlightNum) != NULL)
//		{
//			results.push_back(record);
//		}
//	}
//}




