#pragma once
#include "GuiFrame.h"
#include "KeyMapping.h"

class Creature;
class GuiCreature : public GuiFrame
{
public:
	const TCODColor HEALTH_MAX_COLOR = TCODColor::darkGreen;
	const TCODColor HEALTH_MIN_COLOR = TCODColor::lightRed;

	Creature *currentCreature = nullptr;

	void setCurrentCreature(Creature &creature);
	void GuiFrame::render();

	GuiCreature() : GuiFrame(KEY_UNDEFINED, false){};
};

