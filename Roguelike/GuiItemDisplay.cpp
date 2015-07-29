#include "GuiItemDisplay.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

void GuiItemDisplay::display(Item *item){
	clear();
	if (item != nullptr){
		if (item->isWeapon()) guiWeapon.setCurrentWeapon(static_cast<Weapon*>(item));
		else if (item->isArmor()) guiArmor.setCurrentArmor(static_cast<Armor*>(item));
		else if (item->type == Item::POTION) guiPotion.setCurrentPotion(static_cast<Potion*>(item));
	}
}

void GuiItemDisplay::clear(){
	guiArmor.setCurrentArmor(nullptr);
	guiWeapon.setCurrentWeapon(nullptr);
	guiPotion.setCurrentPotion(nullptr);
}

void GuiItemDisplay::renderTo(GuiFrame &frame, Rectangle &bounds){
	guiArmor.renderTo(frame, bounds);
	guiWeapon.renderTo(frame, bounds);
	guiPotion.renderTo(frame, bounds);
}