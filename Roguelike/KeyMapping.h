#pragma once
#include "libtcod.hpp"
#include "Point2D.h"

class KeyMapping
{
public:
	static Point2D direction(TCOD_keycode_t keyCode);

	KeyMapping(){};
};

const char KEY_LOG = 'L';
const char KEY_STATISTICS = 'S';
const char KEY_QUEST = 'q';
const char KEY_INVENTORY = 'i';
const char KEY_HELP = 'h'; 
const char KEY_INSPECT = 'k'; //look
const char KEY_SKILL = 's';

const char KEY_TALK = 't';
const char KEY_TAKE = 'l'; //loot
const char KEY_ATTACK = 'a';
const char KEY_OPERATE = 'o';
const char KEY_ENTER_AREA = '>';
const char KEY_LEAVE_AREA = '<';

const char KEY_DEBUG = 'v';

const char KEY_UNDEFINED = 0;