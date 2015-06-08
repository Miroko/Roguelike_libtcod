#pragma once
#include "GuiFrame.h"
class QuestFrame : public GuiFrame
{
public:
	void GuiFrame::render(float elapsed);
	bool GuiFrame::handleKey(TCOD_key_t key);

	QuestFrame(std::string name, bool open, float alphaFg, float alphaBg) : GuiFrame(name, open, alphaFg, alphaBg){};
};

