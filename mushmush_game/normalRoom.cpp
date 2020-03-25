#include "normalRoom.h"
#include "mush.h"
#include "bat1.h"
#include "pir1.h"
normal_room::normal_room(int tunnel1, int tunnel2, int tunnel3) : Room(tunnel1, tunnel2, tunnel3)
{
	_near_hazard = new string[3];
	_near_hazard[0] = "no hazard";
	_near_hazard[1] = "no hazard";
	_near_hazard[2] = "no hazard";
	_loc_hazard = nullptr;

}

void normal_room::init_near(const string& eventName)
{


	for (int i = 0; i < 3; i++)
	{

		if (_near_hazard[i] == "no hazard")
		{
			_near_hazard[i] = eventName;
			break;
		}

	}
}
void normal_room::init_hazard(const string&type_hazatd)
{

	if (type_hazatd == "MushMush")
	{

		_loc_hazard = new mushmush("MushMush ");

	}
	if (type_hazatd == "Bat")
	{

		_loc_hazard = new bat("Bat");

	}
	if (type_hazatd == "Pir")
	{
		_loc_hazard = new pir("Pir");

	}
	if (type_hazatd == "empty")
	{
		_hazard = nullptr;
	}

}
bool normal_room::attackInRoom(string& message) const
{

	if (typeid(*_loc_hazard) == typeid(mushmush))
	{
		message = "You got MushMush";
		return 0;
	}
	if (typeid(*_loc_hazard) == typeid(bat))
	{
		message = "Bat is laughin";
		return 1;
	}
	if (typeid(*_loc_hazard) == typeid(pir))
	{
		message = "Pit is whistling";
		return 1;
	}
}
string normal_room::roomHazard() const
{
	string message;
	if (typeid(*_loc_hazard) == typeid(mushmush))
	{
		message = " MushMush is near";
		return message;
	}
	if (typeid(*_loc_hazard) == typeid(bat))
	{
		message = "Bat is near";
		return message;

	}
	if (typeid(*_loc_hazard) == typeid(pir))
	{
		message = "Pit is near";
		return message;
	}
}
bool normal_room::isMushMushHere() const
{
	if (typeid(*_loc_hazard) == typeid(mushmush))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
bool normal_room::clashInRoom(string& msg) const
{

	if (_loc_hazard == nullptr)
	{
		return 0;
	}
	else
	{
		msg = _loc_hazard->strClash();
		return 1;
	}

}