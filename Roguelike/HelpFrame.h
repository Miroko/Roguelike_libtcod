#pragma once
#include "GuiFrame.h"
class HelpFrame : public GuiFrame
{
public:
	void GuiFrame::render(float elapsed);
	bool handleKey(TCOD_key_t key, bool &requireUpdate);

	HelpFrame(std::string name, char controlKey, bool open, float alphaFg, float alphaBg) : GuiFrame(name, controlKey, open, alphaFg, alphaBg){};
};

