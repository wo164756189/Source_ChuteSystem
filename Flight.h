#ifndef FLIGHT_H
#define FLIGHT_H

#include <list>
using namespace std;

// һ����¼
class Flight
{
public:
	Flight() : seat(0) {}

public:
	char FlightNum[32];
	int seat;
};

// �б�
typedef list<Flight> FlightList;

#endif

