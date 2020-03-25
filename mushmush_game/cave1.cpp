#define _CRT_SECURE_NO_WARNINGS
#include "cave1.h"
#include "room1.h"
#include "mush.h"
#include "bat1.h"
#include "pir1.h"
#include "normalRoom.h"
#include "sealedRoom.h"

Cave::Cave(const int*  sealedRooms, int size)
{

	_arryroom[0] = new normal_room(19, 2, 18);
	_arryroom[1] = new normal_room(18, 17, 5);
	_arryroom[2] = new normal_room(17, 0, 4);
	_arryroom[3] = new normal_room(16, 19, 7);
	_arryroom[4] = new normal_room(15, 2, 6);
	_arryroom[5] = new normal_room(9, 1, 14);
	_arryroom[6] = new normal_room(13, 8, 4);
	_arryroom[7] = new normal_room(12, 11, 3);
	_arryroom[8] = new normal_room(11, 6, 10);
	_arryroom[9] = new normal_room(10, 13, 5);
	_arryroom[10] = new normal_room(9, 12, 8);
	_arryroom[11] = new normal_room(15, 7, 8);
	_arryroom[12] = new normal_room(10, 14, 7);
	_arryroom[13] = new normal_room(6, 9, 17);
	_arryroom[14] = new normal_room(12, 5, 16);
	_arryroom[15] = new normal_room(11, 4, 11);
	_arryroom[16] = new normal_room(18, 14, 3);
	_arryroom[17] = new normal_room(13, 2, 1);
	_arryroom[18] = new normal_room(1, 0, 16);
	_arryroom[19] = new normal_room(15, 0, 3);
	for (int i = 0; i < size; i++)
	{
		int ind = sealedRooms[i];
		int tul1 = _arryroom[ind]->getTunnel1data();
		int tul2 = _arryroom[ind]->getTunnel1data();
		int tul3 = _arryroom[ind]->getTunnel1data();
		delete _arryroom[ind];
		_arryroom[ind] = new sealed_room(tul1, tul2, tul3);
	}
	if_over = START;
}
void Cave::plotHazard(int idx, const string& eventName)
{
	const char* error_idx = "Invalid Index Exception";
	const char* error_Hazard = "Invalid Hazard Exception";
	if (idx < 0 || idx>19)
	{
		throw error_idx;
	}
	else
	{
		if (eventName != "Bat"&&eventName != "Pit"&&eventName != "MushMush")
		{
			throw error_Hazard;
		}
		else
		{

			string near;
			if (eventName == "Bat") { near = "Bat is near"; }
			if (eventName == "Pit") { near = "Pit is near"; }
			if (eventName == "MushMush") { near = "MushMush is near"; }

			int nabers = 0;
			_arryroom[idx]->init_hazard(eventName);
			nabers = _arryroom[idx]->getTunnel1data();
			_arryroom[nabers]->init_near(near);
			nabers = _arryroom[idx]->getTunnel2data();
			_arryroom[nabers]->init_near(near);
			nabers = _arryroom[idx]->getTunnel3data();
			_arryroom[nabers]->init_near(near);
		}
	}
}
int Cave::findMushMush() const
{
	const char* error_idx = "Not Found Mushmush Exception";
	int i = 0;
	for (; i < 20; i++)
	{
		if (typeid(_arryroom[i]->getHazard()) == typeid(mushmush))
		{
			return i;

		}
	}


	//throw error_idx;

}
void Cave::hazardNearPlayer(string* hazards) const
{
	string tmp = _arryroom[_index_player]->get_near1();
	if (tmp != "no hazard")
	{
		hazards[0] = _arryroom[_index_player]->get_near1();
	}
	tmp = _arryroom[_index_player]->get_near2();
	if (tmp != "no hazard")
	{
		hazards[1] = _arryroom[_index_player]->get_near2();
	}
	tmp = _arryroom[_index_player]->get_near2();
	if (tmp != "no hazard")
	{
		hazards[2] = _arryroom[_index_player]->get_near3();
	}

}

void Cave::plotPlayerIdx(int idx)
{
	const char* error_idx = "Invalid Index Exception";
	if (idx >= 0 && idx < 20)
	{
		_index_player = idx;
	}
	else
	{
		throw error_idx;
	}
}
const Room* Cave::getRoomAtIndex(int index) const
{

	if (index >= 0 && index < 20)
	{
		return _arryroom[index];
	}
	else
	{
		const char* error_idx = "Invalid Index Exception";
		throw error_idx;
	}

}
void Cave::movePlayer(int idx)
{
	const char* error_idx = "Invalid Index Exception";
	bool result = ligal_move(idx);
	if (_index_player == idx)
	{
		result = 1;
	}

	if (idx < 0 || idx > 19 || result == 0)
	{
		throw error_idx;

	}
	int ligal_loc = _arryroom[_index_player]->getTunnel1data();

	if (ligal_loc == idx)
	{
		_index_player = idx;
	}
	else
	{
		ligal_loc = _arryroom[_index_player]->getTunnel2data();

		if (ligal_loc == idx)
		{
			_index_player = idx;
		}
		else
		{
			ligal_loc = _arryroom[_index_player]->getTunnel3data();

			if (ligal_loc == idx)
			{
				_index_player = idx;
			}
			else
			{
				throw error_idx;
			}
		}
	}

	return;
}

string Cave::playerAttack(int idx) throw(const char*)
{

	const char* error = "Invalid Index Exception";
	bool result = ligal_move(idx);
	if (_index_player == idx)
	{
		result = 1;
	}

	if (idx < 0 || idx >= 20 || result == 0)
	{
		throw  error;

	}
	int loaction[3];

	loaction[0] = _arryroom[_index_player]->getTunnel1data();
	loaction[1] = _arryroom[_index_player]->getTunnel2data();
	loaction[2] = _arryroom[_index_player]->getTunnel3data();

	if (idx == loaction[0] || idx == loaction[1] || idx == loaction[2])
	{
		int idx_mush = findMushMush();
		int move_mush;
		if (typeid(*_arryroom[idx]) == typeid(sealed_room))
		{
			string message;
			if_over = FAILED;
			return message;
		}
		else
		{
			string message;
			bool result;
			int notmove = 0;
			int empty;
			result = _arryroom[idx]->attackInRoom(message);
			if (message == "You got MushMush")
			{
				if_over = WIN;
				return message;
			}
			else
			{

				move_mush = _arryroom[idx_mush]->getTunnel1data();
				empty = _arryroom[move_mush]->roomIsEmpty();
				if (empty == 1) {}

				else
				{
					move_mush = _arryroom[idx_mush]->getTunnel2data();
					empty = _arryroom[move_mush]->roomIsEmpty();
					if (empty == 1) {}
					else
					{
						move_mush = _arryroom[idx_mush]->getTunnel3data();
						empty = _arryroom[move_mush]->roomIsEmpty();
						if (empty == 1) {}
						else
							notmove = 1;

					}
				}
			}

			if (notmove == 0)
			{
				string empty = "empty";
				_arryroom[idx_mush]->init_hazard(empty);
				_arryroom[move_mush]->init_hazard("MushMush");

			}
		}
	}
	else
	{
		throw error;
	}
}
string Cave::playerClash(int idx)
{
	const char* error = "Invalid Index Exception";
	string str;
	bool ligal = ligal_move(idx);
	bool j = _arryroom[_index_player]->clashInRoom(str);
	if (idx < 0 || idx >19 || ligal == 0)
	{
		idx = idx - 2;
		string p3 = "Invalid Index Exception";
		return p3;

	}
	if (str == "MushMush got you")
	{

		if_over = WIN;
		string p1 = "MushMush";
		return p1;

	}
	if (str == "You fell into a Pit")
	{
		if_over = FAILED;
		string p = "Pit";
		return p;
	}
	if (str.empty())
	{
		string p3 = "no hazard";
		return p3;
	}

	if (str == "A Bat will move you")
	{
		string empty = "empty";
		movePlayer(idx);
		string s = playerClash(idx + 2);
		_arryroom[_index_player]->init_hazard(empty);
		return s;

	}




}
bool Cave::gameOver() const
{
	bool ifcountinue;
	if (if_over == COUNTINUE || if_over == START)
	{

		return 0;
	}
	else
	{
		ifcountinue = 1;
		return 1;
	}

}
bool Cave::ligal_move(int idx) const
{
	int t1 = _arryroom[_index_player]->getTunnel1data();
	int t2 = _arryroom[_index_player]->getTunnel2data();
	int t3 = _arryroom[_index_player]->getTunnel3data();
	if (idx == t1 || idx == t2 || idx == t3)
	{

		return 1;
	}
	else
		return 0;
}



Cave::~Cave()
{

	for (int i = 0; i < 20; i++)
	{
		_arryroom[i]->~Room();
		delete _arryroom[i];
	}
}