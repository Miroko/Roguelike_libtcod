#pragma once
#include "GuiFrame.h"

class HelpFrame : public GuiFrame
{
public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	HelpFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg){};
};

