#include "ChannelDlgFile.h"


ChannelDlgFile::ChannelDlgFile()
{
}


ChannelDlgFile::~ChannelDlgFile()
{
}

//int datasource::load()
//{
//	file* fp = fopen("channel.data", "rb");
//	if (!fp) return 0;
//
//	m_records.clear(); // 清空
//
//	// 加载数据	
//	while (!feof(fp))
//	{
//		flight record;
//		int n = fread(&record, 1, sizeof(flight), fp);
//		if (n < 0) break;
//		if (n == 0) continue;
//
//		m_records.push_back(record);
//	}
//
//	fclose(fp);
//	return 0;
//}
//
//// 保存
//int datasource::save()
//{
//	file* fp = fopen("channel.data", "wb");
//	if (!fp) return -1;
//
//	// 保存每条记录
//	for (flightlist::iterator iter = m_records.begin();
//		iter != m_records.end(); iter++)
//	{
//		flight& record = *iter;
//		fwrite(&record, 1, sizeof(flight), fp);
//	}
//
//	fclose(fp);
//	return 0;
//}