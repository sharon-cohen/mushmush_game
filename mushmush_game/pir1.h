
#pragma once
#include "hazard1.h"
class pir : public Hazard1
{

public:
	pir(const char * str) :Hazard1(str) {}
	virtual string strClash();
};
