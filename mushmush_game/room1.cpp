#define _CRT_SECURE_NO_WARNINGS
#include "room1.h"
#include "hazard1.h"
#include <sstream>
#include <cstring>
#include "sealedRoom.h"
Room::Room(int tunnel1, int tunnel2, int tunnel3)
{
	_tunnels[0] = tunnel1;
	_tunnels[1] = tunnel2;
	_tunnels[2] = tunnel3;
	_hazard = nullptr;
}

int Room::getTunnel1() const
{
	if (_tunnels[1] > _tunnels[0]) {
		if (_tunnels[2] > _tunnels[1]) {
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (_tunnels[2] > _tunnels[0]) {

			return 2;
		}
		else
			return 0;
	}

}
int Room::getTunnel2() const
{
	int val = getTunnel1();
	if (val == 0)
	{
		if (_tunnels[2] > _tunnels[1])
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (val == 1)
		{
			if (_tunnels[2] > _tunnels[0])
			{
				return 2;
			}
			else
			{
				return 0;
			}
		}

		if (val == 2)
		{
			if (_tunnels[1] > _tunnels[0])
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}

	return 0;
}



int Room::getTunnel3() const
{
	if (getTunnel2() != 0 && getTunnel1() != 0) { return 0; }
	if (getTunnel2() != 1 && getTunnel1() != 1) { return 1; }
	if (getTunnel2() != 2 && getTunnel1() != 2) { return 2; }

}
Room ::~Room() {};

static std::string expectedResults[] =
{
	"Bat is nearPit is nearMushMush is nearYou got MushMush1"
};

static std::string getStatusString(const Cave& c)
{
	string near_player[3];
	c.hazardNearPlayer(near_player);

	return near_player[0] + near_player[1] + near_player[2];
}

static std::string integerToString(int x)
{
	std::stringstream s;
	s << x;
	return s.str();
}

static bool test(void)
{
	Cave cave(NULL, 0);
	std::string status;
	cave.plotPlayerIdx(1);
	cave.plotHazard(9, "MushMush");
	cave.plotHazard(2, "Pit");
	cave.plotHazard(18, "Bat");

	status += getStatusString(cave);
	bool gotException = false;
	try
	{
		cave.movePlayer(1);
		status += getStatusString(cave);
		//status += cave.playerClash(1);
	}
	catch (const char* p)
	{

		gotException = (0 == strcmp(p, "Invalid Index Exception"));
	}
	if (!gotException)
		std::cout << "Error: Incorrectly Handled Exception\n";
	cave.movePlayer(17);
	status += getStatusString(cave);
	cave.movePlayer(13);
	status += getStatusString(cave);
	status += cave.playerAttack(9);
	status += integerToString(cave.gameOver());
	return status == expectedResults[0];
}
int main()
{
	if (!test())
		std::cout << "Error: Game Logic Error\n";
	Room* r = new sealed_room(1, 2, 3);
	delete r;
	cin.get();

}



