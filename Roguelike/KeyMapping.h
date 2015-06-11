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
const char KEY_QUEST = 'q';
const char KEY_INVENTORY = 'i';
const char KEY_EQUIPMENT = 'e';
const char KEY_HELP = 'h';
const char KEY_LEAVE_AREA = 'l';

const char KEY_TAKE = 't';
const char KEY_ATTACK = 'a';

const char UNDEFINED = 0;