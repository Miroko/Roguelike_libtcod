#include "GuiWeapon.h"
#include "Weapon.h"
#include "GuiFrame.h"

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
			currentWeapon->rarity.color * Gui::RARITY_COLOR_MULTIPLIER,
			TCOD_CENTER,
			currentWeapon->rarity.name);
		//description
		offsetY += 1;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0, 
			currentWeapon->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, 
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
		//mods
		offsetY += 1;
		for (auto &mod : currentWeapon->rarityMods){
			offsetY += 1;
			frame.printString(
				bounds.start.x + 1, bounds.start.y + offsetY,
				bounds.getWidth(), 0, 
				Gui::FRAME_FG, 
				TCOD_CENTER, 
				mod->effect->getDescription());
		}
	}
}
