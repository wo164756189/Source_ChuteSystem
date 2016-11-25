#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "Flight.h"

class DataSource
{
public:
	DataSource();
	~DataSource();

public:
	// ����
	int load();

	// ����
	int save();

	// ���
	int add(const Flight& Fly);

	FlightList& list() { return m_records; }

	// ɾ��
	void remove(const char* FlightNum);

	// ���ɻ��Ų��� 
	//Flight* find(const char* FlightNum);

	// ���ɻ���ƥ�����
	//void match(const char* FlightNum, FlightList& results);

private:
	char m_filename[256];
	FlightList m_records; // ���зɻ�
};





#endif


