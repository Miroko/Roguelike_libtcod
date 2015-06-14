#pragma once
#include "GuiFrame.h"

class StatisticsFrame : public GuiFrame
{
private:
	const TCODColor healthMaxColor = TCODColor::darkGreen;
	const TCODColor healthMinColor = TCODColor::lightRed;
public:
	void GuiFrame::render(float elapsed);
	bool handleKey(TCOD_key_t key);

	StatisticsFrame(std::string name, char controlKey, bool open, float alphaFg, float alphaBg) : GuiFrame(name, controlKey, open, alphaFg, alphaBg){};
};

