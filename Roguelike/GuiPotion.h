#pragma once
#include "GuiFrame.h"
#include "KeyMapping.h"

class Potion;
class GuiPotion : public GuiFrame
{
public:
	Potion *currentPotion = nullptr;

	void setCurrentPotion(Potion &potion);
	void GuiFrame::render();

	GuiPotion() : GuiFrame(KEY_UNDEFINED, false){};
};

