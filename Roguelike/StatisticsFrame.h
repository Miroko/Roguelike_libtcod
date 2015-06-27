#pragma once
#include "GuiFrame.h"

class StatisticsFrame : public GuiFrame
{
private:
	const TCODColor healthMaxColor = TCODColor::darkGreen;
	const TCODColor healthMinColor = TCODColor::lightRed;
public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key, bool &requireUpdate);

	StatisticsFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Statistics"){};
};

