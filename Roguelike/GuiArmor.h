#pragma once
#include "GuiFrame.h"
#include "KeyMapping.h"

class Armor;
class GuiArmor : public GuiFrame
{
public:
	Armor *currentArmor = nullptr;

	void setCurrentArmor(Armor &armor);
	void GuiFrame::render();

	GuiArmor() : GuiFrame(KEY_UNDEFINED, false){};
};

