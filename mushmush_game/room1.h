#define _CRT_SECURE_NO_WARNINGS
#include "cave1.h"
#pragma once
using namespace std;

//#pragma pack(push, 1)
class Hazard1;
class Room
{
protected:
	const Hazard1* _hazard;
private:
	int _tunnels[3];

public:
	Room(int tunnel1, int tunnel2, int tunnel3);
	
	virtual bool attackInRoom(string& message) const = 0;
	virtual void init_hazard(const string& hazard) = 0;
	int getTunnel1() const;
	int getTunnel2() const;
	int getTunnel3() const;
	virtual string roomHazard() const = 0;
	virtual const  Hazard1* getHazard() const = 0;
	virtual bool roomIsEmpty() const = 0;
	virtual bool isMushMushHere() const = 0;
	virtual bool clashInRoom(std::string& msg)const = 0;
	virtual string getstr() = 0;
	virtual  string  get_near1()const = 0;
	virtual  string  get_near2()const = 0;
	virtual  string  get_near3()const = 0;
	virtual void init_near(const string& eventName) = 0;
	int getTunnel1data()const { return _tunnels[0]; }
	int getTunnel2data() const { return _tunnels[1]; }
	int getTunnel3data() const { return _tunnels[2]; }

	virtual ~Room();

};
//#pragma pack(pop)