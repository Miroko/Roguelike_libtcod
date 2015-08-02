#pragma once
#include "GuiComponent.h"
#include "GuiCreature.h"
#include "GuiArmor.h"
#include "GuiWeapon.h"
#include "GuiPotion.h"
#include "GuiOperable.h"
#include "GuiTile.h"

class GameObject;
class GuiGameObjectDisplay : public GuiComponent
{
private:
	GuiCreature guiCreature;
	GuiWeapon guiWeapon;
	GuiArmor guiArmor;
	GuiPotion guiPotion;
	GuiOperable guiOperatable;
	GuiTile guiTile;

public:
	void clear();
	void setDisplayedObject(GameObject *object);

	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiGameObjectDisplay() : GuiComponent(){};
};

