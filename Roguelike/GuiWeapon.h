#pragma once
#include "GuiFrame.h"
#include "KeyMapping.h"

class Weapon;
class GuiWeapon : public GuiFrame
{
public:
	Weapon *currentWeapon = nullptr;

	void setCurrentWeapon(Weapon &weapon);
	void GuiFrame::render();

	GuiWeapon() : GuiFrame(KEY_UNDEFINED, false){};
};

