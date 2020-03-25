
#define MUSH_H
#pragma once
#include "hazard1.h"
class mushmush : public Hazard1
{

public:

	mushmush(const char * str) :Hazard1(str) { }
	virtual  string strClash();

};