#include "GuiPotion.h"
#include "Potion.h"
#include "Gui.h"
#include "GuiFrame.h"

void GuiPotion::setCurrentPotion(Potion *potion){
	currentPotion = potion;
}
void GuiPotion::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (currentPotion != nullptr){
		//description
		int offsetY = 0;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0, 
			currentPotion->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, 
			TCOD_CENTER, 
			currentPotion->getDescription());
		//stats
		offsetY += 2;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY, 
			bounds.getWidth(), 0, 
			Gui::FRAME_FG, 
			TCOD_CENTER, 
			currentPotion->getStatistics());
		//effects
		offsetY += 1;
		for (auto &effect : currentPotion->effects){
			offsetY += 1;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0, 
				Gui::FRAME_FG, 
				TCOD_CENTER, 
				effect->getDescription());
		}
	}
}
