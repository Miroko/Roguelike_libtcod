#include "GuiArmor.h"
#include "Armor.h"
#include "Gui.h"

void GuiArmor::setCurrentArmor(Armor &armor){
	currentArmor = &armor;
}
void GuiArmor::render(){
	GuiFrame::render();
	if (currentArmor != nullptr){
		int offsetY = 0;
		//description + stats
		printString(0, offsetY, getWidth(), 1, currentArmor->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE,
			currentArmor->getDescription());
		printString(0, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_BG, TCOD_RIGHT, TCOD_BKGND_NONE,
			currentArmor->getStatistics());
		offsetY += 1;
		//mods
		for (auto &mod : currentArmor->rarityMods){
			printString(0, offsetY, getWidth(), 1, currentArmor->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE, mod->name);
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
