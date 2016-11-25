#ifndef FLIGHT_H
#define FLIGHT_H

#include <list>
using namespace std;

// 一条记录
class Flight
{
public:
	Flight() : seat(0) {}

public:
	char FlightNum[32];
	int seat;
};

// 列表
typedef list<Flight> FlightList;

#endif

