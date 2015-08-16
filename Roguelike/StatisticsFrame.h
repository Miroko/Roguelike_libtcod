#pragma once
#include "GuiFrame.h"
#include "GuiCreature.h"

class StatisticsFrame : public GuiFrame
{
private:
	Rectangle guiCreatureBounds;
	GuiCreature guiCreature;

public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	void init(Rectangle &bounds);

	StatisticsFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Statistics"){};
};

