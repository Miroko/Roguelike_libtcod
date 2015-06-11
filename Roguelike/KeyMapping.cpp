#include "KeyMapping.h"
#include "Direction.h"

Point2D KeyMapping::direction(TCOD_keycode_t keyCode){
	switch (keyCode) {
	case TCODK_KP1: return DOWN_LEFT;
	case TCODK_KP4: return LEFT;
	case TCODK_KP7: return UP_LEFT;
	case TCODK_KP8: return UP;
	case TCODK_KP9: return UP_RIGHT;
	case TCODK_KP6: return RIGHT;
	case TCODK_KP3: return DOWN_RIGHT;
	case TCODK_KP2: return DOWN;
	case TCODK_KP5: return CENTER;
	default: return Point2D(); //Undefined point
	}
}