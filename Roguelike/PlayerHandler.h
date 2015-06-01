#pragma once
#include "AliveObject.h"
#include "Quest.h"
#include "memory"
class PlayerHandler
{
public:
	std::shared_ptr<AliveObject> playerObject;

	// Controls
	bool handleKey(TCOD_key_t key);

	bool leaveArea(char keyChar);
	bool move(TCOD_keycode_t code);
	//----

	PlayerHandler(){};
};

