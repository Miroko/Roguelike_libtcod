#include "GuiWeapon.h"
#include "Weapon.h"

void GuiWeapon::setCurrentWeapon(Weapon &weapon){
	currentWeapon= &weapon;
}
void GuiWeapon::render(){
	GuiFrame::render();
	if (currentWeapon != nullptr){
		int offsetY = 0;
		//description + stats
		printString(0, offsetY, getWidth(), 1, currentWeapon->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE,
			currentWeapon->getDescription());
		printString(0, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_BG, TCOD_RIGHT, TCOD_BKGND_NONE,
			currentWeapon->getStatistics());
		offsetY += 1;
		//mods
		for (auto &mod : currentWeapon->rarityMods){
			printString(0, offsetY, getWidth(), 1, currentWeapon->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE, mod->name);
			++offsetY;
			//effects
			for (auto &effect : mod->effects){
				printString(1, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE, "-" + effect->getDescription());
				++offsetY;
			}
		}
	}
	blit();
}
