#pragma once
#include "AliveObject.h"
#include "Quest.h"
#include "memory"
class PlayerHandler
{
public:
	std::shared_ptr<AliveObject> playerObject;
	//Items
	std::vector<std::shared_ptr<Item>> items;
	void addItem(std::shared_ptr<Item> item);
	//----

	// Controls
	bool handleKey(TCOD_key_t key);

	bool move(TCOD_key_t key);
	bool attack(TCOD_key_t key);

	void leaveArea(TCOD_key_t key);
	void inventory(TCOD_key_t key);
	//----

	PlayerHandler(){};
};

