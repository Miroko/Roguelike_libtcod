#pragma once
#include "GuiComponent.h"

class GuiFrame;
class Armor;
class GuiArmor : public GuiComponent
{
public:
	Armor *currentArmor = nullptr;

	void setCurrentArmor(Armor *armor);
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiArmor() : GuiComponent(){};
};

