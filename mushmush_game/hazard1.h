
#define HAZARD_H
#pragma once
#include "room1.h"
#include <string>
using namespace std;
class Hazard1
{
protected:
	string  _type_hazard;

public:
	Hazard1(const char*str_type) {
		_type_hazard = str_type;

	}
	virtual string  strClash() { return 0; }
	void init_str(const char*str_type) {
		_type_hazard = str_type;
	}
};
