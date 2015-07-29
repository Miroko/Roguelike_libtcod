#pragma once
#include "GuiComponent.h"

class GuiFrame;
class Weapon;
class GuiWeapon : public GuiComponent
{
public:
	Weapon *currentWeapon = nullptr;

	void setCurrentWeapon(Weapon *weapon);
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiWeapon() : GuiComponent(){};
};

