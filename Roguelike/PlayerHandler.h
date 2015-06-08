#pragma once
#include "AliveObject.h"
#include "Quest.h"
#include "Direction.h"
#include <memory>
class PlayerHandler
{
private:
	//True if player moved or waited
	bool move(TCOD_key_t key);

	//True if attacked
	bool attack();

	//Take items at player location
	//True if took something
	bool take();

	bool leaveArea();
	bool InventoryFrame();
	bool equipment();
	bool quest();
	bool help();

public:
	std::shared_ptr<AliveObject> playerCreature;

	//True if simulation update needed
	bool handleKey(TCOD_key_t key);

	PlayerHandler(){};
};

