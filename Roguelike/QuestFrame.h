#pragma once
#include "GuiFrame.h"

class QuestFrame : public GuiFrame
{
public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	QuestFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Quest"){};
};

