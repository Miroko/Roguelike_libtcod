#include "GuiArmor.h"
#include "Gui.h"
#include "GuiFrame.h"
#include "Armor.h"

void GuiArmor::setCurrentArmor(Armor *armor){
	currentArmor = armor;
}
void GuiArmor::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (currentArmor != nullptr){
		//rarity
		int offsetY = 0;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			currentArmor->rarity.color * Gui::RARITY_COLOR_MULTIPLIER,
			TCOD_CENTER,
			currentArmor->rarity.name);
		//description
		offsetY += 1;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY, 
			bounds.getWidth(), 0, 
			currentArmor->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, 
			TCOD_CENTER,
			currentArmor->getDescription());
		//stats
		offsetY += 2;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0, 
			Gui::FRAME_FG, 
			TCOD_CENTER,
			currentArmor->getStatistics());
		//mods
		offsetY += 1;
		for (auto &mod : currentArmor->rarityMods){
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
