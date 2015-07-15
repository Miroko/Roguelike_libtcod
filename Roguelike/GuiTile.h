#pragma once
#include "GuiFrame.h"
#include "KeyMapping.h"

class Tile;
class GuiTile : public GuiFrame
{
public:
	Tile *currentTile = nullptr;

	void setCurrentTile(Tile &tile);
	void GuiFrame::render();

	GuiTile() : GuiFrame(KEY_UNDEFINED, false){};
};