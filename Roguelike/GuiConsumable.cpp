#include "GuiConsumable.h"
#include "Gui.h"
#include "GuiFrame.h"
#include "Consumable.h"

void GuiConsumable::setCurrentConsumable(Consumable *consumable){
	currentConsumable = consumable;
}
void GuiConsumable::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (currentConsumable != nullptr){
		//rarity
		int offsetY = 0;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			currentConsumable->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
			TCOD_CENTER,
			currentConsumable->rarityType->name);
		//description
		offsetY += 1;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0, 
			currentConsumable->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER, 
			TCOD_CENTER, 
			currentConsumable->getDescription());
		//stats
		offsetY += 2;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY, 
			bounds.getWidth(), 0, 
			Gui::FRAME_FG, 
			TCOD_CENTER, 
			currentConsumable->getStatistics());
		//affixes
		offsetY += 1;
		for (auto &affix : currentConsumable->rarityAffixes){
			offsetY += 1;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0, 
				Gui::FRAME_FG, 
				TCOD_CENTER, 
				affix->getDescription());
		}
	}
}
