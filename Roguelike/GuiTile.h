#pragma once
#include "GuiComponent.h"

class GuiFrame;
class Tile;
class GuiTile : public GuiComponent
{
public:
	Tile *currentTile = nullptr;

	void setCurrentTile(Tile *tile);
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiTile(){};
};