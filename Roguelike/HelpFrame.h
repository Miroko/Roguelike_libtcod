#pragma once
#include "GuiFrame.h"
class HelpFrame : public GuiFrame
{
public:
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key, bool &requireUpdate);

	HelpFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg){};
};

