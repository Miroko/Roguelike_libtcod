#pragma once
#include "GuiFrame.h"

class StatisticsFrame : public GuiFrame
{
private:
	Rectangle creatureBounds;

public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	void init(Rectangle &bounds);

	StatisticsFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Statistics"){};
};

