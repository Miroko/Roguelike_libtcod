#pragma once
#include "AliveObject.h"
#include "Quest.h"
#include "Direction.h"
#include <memory>
class PlayerController
{
private:
	//True if player moved or waited
	bool move(TCOD_key_t key);

	//True if attacked
	bool attack();

	//Take items at player location
	//True if picker opened
	bool take();

	//True if opened something
	bool operate();

public:
	std::shared_ptr<AliveObject> playerCreature;

	//True if simulation update needed
	bool handleKey(TCOD_key_t key);

	PlayerController(){};
};

