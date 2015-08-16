#include "GuiCreature.h"
#include "Creature.h"
#include "Engine.h"
#include "Weapon.h"
#include "Armor.h"
#include "GuiFrame.h"
#include "Gui.h"

void GuiCreature::setCurrentCreature(Creature *creature){
	currentCreature = creature;
}
void GuiCreature::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (currentCreature != nullptr){
		int offsetY = 0;
		//Creature
		//rarity
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			currentCreature->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
			TCOD_CENTER,
			currentCreature->rarityType->name);
		offsetY += 1;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			currentCreature->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER, 
			TCOD_CENTER, 
			currentCreature->name);
		//affixes
		for (auto &affix : currentCreature->rarityAffixes){
			offsetY += 1;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_CENTER,
				affix->getDescription());
		}
		//healthCurrent
		offsetY += 2;
		double percentage = ((double)currentCreature->healthCurrent / (double)currentCreature->healthMax);
		TCODColor healthColor = TCODColor::lerp(HEALTH_MIN_COLOR, HEALTH_MAX_COLOR, percentage);
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			Gui::FRAME_FG, 
			TCOD_LEFT, 
			"Health");
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY, 
			bounds.getWidth(), 0,
			healthColor,
			TCOD_RIGHT,
			engine::string.outOf(currentCreature->healthCurrent, currentCreature->healthMax));
		//stamina
		offsetY += 1;
		percentage = ((double)currentCreature->staminaCurrent / (double)currentCreature->staminaMax);
		TCODColor staminaColor = TCODColor::lerp(STAMINA_MIN_COLOR, STAMINA_MAX_COLOR, percentage);
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Stamina");
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			staminaColor,
			TCOD_RIGHT,
			engine::string.outOf(currentCreature->staminaCurrent, currentCreature->staminaMax));
		//Items
		//items in hold
		auto &items = currentCreature->inventory.getHoldingItems();
		if (!items.empty()){
			offsetY += 2;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_LEFT,
				"Holding");
			for (auto &item : items){
				offsetY += 1;
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					item->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
					TCOD_LEFT,
					item->getDescription());
				if (item->isWeapon()){
					Weapon *weapon = static_cast<Weapon*>(item);
					std::string statistics = engine::string.damage(weapon->getDamage());
					if (weapon->type == GameObject::WEAPON_RANGED) statistics += " " + engine::string.range(weapon->range);
					frame.printString(
						bounds.start.x, bounds.start.y + offsetY,
						bounds.getWidth(), 0,
						Gui::FRAME_FG,
						TCOD_RIGHT,
						statistics);
					//affixes
					for (auto &affix : weapon->rarityAffixes){
						offsetY += 1;
						frame.printString(
							bounds.start.x + 1, bounds.start.y + offsetY,
							bounds.getWidth(), 0,
							Gui::FRAME_FG,
							TCOD_LEFT,
							affix->getDescription());
					}
				}
			}
		}
		//armors
		auto &armors = currentCreature->inventory.getArmors();
		if (!armors.empty()){
			offsetY += 2;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_LEFT,
				"Wearing");
			for (auto &armor : armors){
				offsetY += 1;
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					armor->rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
					TCOD_LEFT,
					armor->getDescription());
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					Gui::FRAME_FG,
					TCOD_RIGHT,
					engine::string.defence(armor->getDefence()));
				//affixes
				for (auto &affix : armor->rarityAffixes){
					offsetY += 1;
					frame.printString(
						bounds.start.x + 1, bounds.start.y + offsetY,
						bounds.getWidth(), 0,
						Gui::FRAME_FG, TCOD_LEFT,
						affix->getDescription());
				}
			}
		}
		//Effects
		auto &effects = currentCreature->effects;
		if (!effects.empty()){
			offsetY += 2;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_LEFT,
				"Effects");
			for (auto &effect : effects){
				offsetY += 1;
				std::string effectString = effect->getDescription();
				int rowsNeededForString = frame.console->getHeightRect(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 2,
					effectString.c_str());
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), rowsNeededForString,
					Gui::FRAME_FG, TCOD_LEFT,
					effectString);
				offsetY += rowsNeededForString - 1;
			}
		}
	}
}

