
#define BAT1_H
#pragma once
#include "hazard1.h"	
class bat : public Hazard1
{

public:
	bat(const char * str) :Hazard1(str) {}
	virtual  string  strClash();

};
