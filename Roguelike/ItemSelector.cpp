#include "ItemSelector.h"
#include "Direction.h"
#include "KeyMapping.h"

bool ItemSelector::handleKey(TCOD_key_t key){
	Point2D direction = KeyMapping::direction(key.vk);
	if (!direction.undefined()){
		if (direction == UP);
		else if (direction == DOWN);
		else if (direction == LEFT);
		else if (direction == RIGHT);
	}
	return true;
}