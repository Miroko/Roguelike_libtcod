#pragma once
#include "GuiComponent.h"
#include "libtcod.hpp"

class GuiFrame;
class Creature;
class GuiCreature : public GuiComponent
{
public:
	const TCODColor HEALTH_MAX_COLOR = TCODColor::darkGreen;
	const TCODColor HEALTH_MIN_COLOR = TCODColor::lightRed;

	Creature *currentCreature = nullptr;

	void setCurrentCreature(Creature *creature);
	void renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiCreature(){};
};

