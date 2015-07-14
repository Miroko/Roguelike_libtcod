#include "GuiPotion.h"
#include "Potion.h"
#include "Gui.h"

void GuiPotion::setCurrentPotion(Potion &potion){
	currentPotion = &potion;
}
void GuiPotion::render(){
	GuiFrame::render();
	if (currentPotion != nullptr){
		int offsetY = 0;
		//description + stats
		printString(0, offsetY, getWidth(), 1, currentPotion->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE,
			currentPotion->getDescription());
		printString(0, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_BG, TCOD_RIGHT, TCOD_BKGND_NONE,
			currentPotion->getStatistics());
		offsetY += 1;
		//effects
		for (auto &effect : currentPotion->effects){
			printString(0, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_BG, TCOD_LEFT, TCOD_BKGND_NONE, effect->getDescription());
			++offsetY;
		}
	}
	blit();
}
