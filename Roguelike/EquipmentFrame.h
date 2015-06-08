#pragma once
#include "GuiFrame.h"
class EquipmentFrame : public GuiFrame
{
public:

	void GuiFrame::render(float elapsed);
	bool GuiFrame::handleKey(TCOD_key_t key);

	EquipmentFrame(std::string name, bool open, float alphaFg, float alphaBg) : GuiFrame(name, open, alphaFg, alphaBg){};
};

