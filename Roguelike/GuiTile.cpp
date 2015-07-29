#include "GuiTile.h"
#include "Tile.h"
#include "Gui.h"
#include "GuiFrame.h"

void GuiTile::setCurrentTile(Tile *tile){
	currentTile = tile;
}
void GuiTile::renderTo(GuiFrame &frame){
	if (currentTile!= nullptr){
		frame.printString(0, 0, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_CENTER, currentTile->getDescription());
	}
}
