#pragma once

class GuiFrame;
class Tile;
class GuiTile
{
public:
	Tile *currentTile = nullptr;

	void setCurrentTile(Tile *tile);
	void renderTo(GuiFrame &frame);

	GuiTile(){};
};