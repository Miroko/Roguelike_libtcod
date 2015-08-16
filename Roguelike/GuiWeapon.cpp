#include "GuiWeapon.h"
#include "Weapon.h"
#include "GuiFrame.h"
#include "Gui.h"

void GuiWeapon::setCurrentWeapon(Weapon *weapon){
	currentWeapon = weapon;
}
void GuiWeapon::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (currentWeapon != nullptr){
		//rarity
		int offsetY = 0;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			currentWeapon->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
			TCOD_CENTER,
			currentWeapon->rarityType->name);
		//description
		offsetY += 1;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0, 
			currentWeapon->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER, 
			TCOD_CENTER, 
			currentWeapon->getDescription());
		//stats
		offsetY += 2;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY, 
			bounds.getWidth(), 0, 
			Gui::FRAME_FG, 
			TCOD_CENTER, 
			currentWeapon->getStatistics());
		//affixes
		offsetY += 1;
		for (auto &affix : currentWeapon->rarityAffixes){
			offsetY += 1;
			frame.printString(
				bounds.start.x + 1, bounds.start.y + offsetY,
				bounds.getWidth(), 0, 
				Gui::FRAME_FG, 
				TCOD_CENTER, 
				affix->getDescription());
		}
	}
}
