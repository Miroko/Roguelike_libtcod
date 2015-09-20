#include "Tile.h"
#include "Engine.h"

void Tile::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	frame.printString(
		renderBounds.start.x, renderBounds.start.y,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getDescription());
}


