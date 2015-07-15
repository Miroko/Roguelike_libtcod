#include "GuiTile.h"
#include "Tile.h"
#include "Gui.h"

void GuiTile::setCurrentTile(Tile &tile){
	currentTile = &tile;
}
void GuiTile::render(){
	GuiFrame::render();
	if (currentTile!= nullptr){
		printString(0, 0, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_LEFT, TCOD_BKGND_NONE,
			currentTile->getDescription());
	}
	blit();
}
