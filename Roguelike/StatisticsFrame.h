#pragma once
#include "GuiFrame.h"
#include "GuiCreature.h"

class StatisticsFrame : public GuiFrame
{
private:
	GuiCreature guiCreature;

public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	StatisticsFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Statistics"){};
};

