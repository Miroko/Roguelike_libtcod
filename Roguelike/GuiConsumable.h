#pragma once
#include "GuiComponent.h"

class GuiFrame;
class Consumable;
class GuiConsumable : GuiComponent
{
public:
	Consumable *currentConsumable = nullptr;

	void setCurrentConsumable(Consumable *consumable);
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiConsumable(){};
};

