#pragma once
#include <list>
#include <QString>

using namespace std;

class HuaCao
{
public:
	HuaCao(){};

	~HuaCao(){};

public:
	char number[32];
};

// �б�
typedef list<HuaCao> HuaCaoList;

