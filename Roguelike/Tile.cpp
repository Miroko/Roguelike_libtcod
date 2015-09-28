#include "Tile.h"
#include "Engine.h"

bool Tile::isPassable(DynamicObject &dynamicObjectMoving){
	if (walkCost <= 0) return false;
	else return true;
}

void Tile::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	frame.printString(
		renderBounds.start.x, renderBounds.start.y,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getDescription());
}


