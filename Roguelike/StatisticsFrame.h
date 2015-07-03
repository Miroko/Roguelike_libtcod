#pragma once
#include "GuiFrame.h"

class StatisticsFrame : public GuiFrame
{
private:
	const TCODColor HEALTH_MAX_COLOR = TCODColor::darkGreen;
	const TCODColor HEALTH_MIN_COLOR = TCODColor::lightRed;
public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	StatisticsFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Statistics"){};
};

