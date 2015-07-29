#pragma once
#include "GuiComponent.h"
#include "GuiArmor.h"
#include "GuiWeapon.h"
#include "GuiPotion.h"

class Item;
class GuiItemDisplay : public GuiComponent
{
private:
	GuiWeapon guiWeapon;
	GuiArmor guiArmor;
	GuiPotion guiPotion;

public:
	void clear();
	void display(Item *item);

	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiItemDisplay() : GuiComponent(){};
};

