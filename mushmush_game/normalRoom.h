#pragma once
#include "room1.h"
#include "mush.h"
#include "bat1.h"
#include "pir1.h"

class normal_room : public Room
{
private:
	const string str_typ = "normal room";
	string*_near_hazard;
	Hazard1* _loc_hazard;

public:
	normal_room(int tunnel1, int tunnel2, int tunnel3);

	virtual string getstr() { return str_typ; }
	virtual  string  get_near1()const { return _near_hazard[0]; }
	virtual  string  get_near2()const { return _near_hazard[1]; }
	virtual  string  get_near3()const { return _near_hazard[2]; }
	virtual void init_near(const string& eventName);
	virtual void init_hazard(const string& hazard);
	virtual const Hazard1* getHazard() const { return _loc_hazard; }
	virtual bool attackInRoom(string& message) const;
	virtual string roomHazard() const;
	virtual bool roomIsEmpty() const {
		if (_loc_hazard == nullptr) return 1;
		else
			return 0;
	}
	virtual bool isMushMushHere() const;
	virtual bool clashInRoom(std::string& msg)const;
	virtual ~normal_room() {
		if (_loc_hazard != nullptr) { delete _loc_hazard; }
	}
};