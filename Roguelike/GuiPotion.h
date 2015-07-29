#pragma once
#include "GuiComponent.h"

class GuiFrame;
class Potion;
class GuiPotion : GuiComponent
{
public:
	Potion *currentPotion = nullptr;

	void setCurrentPotion(Potion *potion);
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiPotion(){};
};

