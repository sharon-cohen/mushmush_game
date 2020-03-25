#pragma once
#include <iostream>
#include <string>
enum  Situ_GAME { START = 0, COUNTINUE, WIN, LOSE, FAILED };
using namespace std;
class Room;
class Cave
{
protected:
	Room* _arryroom[20];
	int _index_player;
	Situ_GAME if_over;
public:

	Cave(const int*  sealedRooms, int size);
	const Room* getRoomAtIndex(int index) const throw(const char*);
	void plotHazard(int idx, const std::string& eventName)throw(const char*);
	void plotPlayerIdx(int idx) throw(const char*);
	int findMushMush() const;
	void movePlayer(int idx) throw(const char*);
	string playerAttack(int idx) throw(const char*);
	string playerClash(int idx) throw(const char*);
	bool gameOver() const;
	void hazardNearPlayer(string* hazards) const;
	bool ligal_move(int idx) const;
	~Cave();
};
