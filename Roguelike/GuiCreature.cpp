#include "GuiCreature.h"
#include "Creature.h"
#include "Engine.h"
#include "Weapon.h"
#include "Armor.h"
#include "GuiFrame.h"

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
			currentCreature->rarity.color * Gui::RARITY_COLOR_MULTIPLIER,
			TCOD_CENTER,
			currentCreature->rarity.name);
		offsetY += 1;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			currentCreature->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, 
			TCOD_CENTER, 
			currentCreature->name);
		//mods
		for (auto &mod : currentCreature->rarityMods){
			offsetY += 1;
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_CENTER,
				mod->effect->getDescription());
		}
		//health
		offsetY += 2;
		float percentage = ((float)currentCreature->health / (float)currentCreature->healthMax);
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
			engine::string.outOf(currentCreature->health, currentCreature->healthMax));
		//stamina
		offsetY += 1;
		percentage = ((float)currentCreature->staminaCurrent / (float)currentCreature->staminaMax);
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
					item->rarity.color * Gui::RARITY_COLOR_MULTIPLIER,
					TCOD_LEFT,
					item->name);
				if (item->isWeapon()){
					Weapon *weapon = static_cast<Weapon*>(item);
					std::string statistics = engine::string.damage(weapon->damage);
					if (weapon->type == GameObject::WEAPON_RANGED) statistics += " " + engine::string.range(weapon->range);
					frame.printString(
						bounds.start.x, bounds.start.y + offsetY,
						bounds.getWidth(), 0,
						Gui::FRAME_FG,
						TCOD_RIGHT,
						statistics);
					//mods
					for (auto &mod : weapon->rarityMods){
						offsetY += 1;
						frame.printString(
							bounds.start.x + 1, bounds.start.y + offsetY,
							bounds.getWidth(), 0,
							Gui::FRAME_FG,
							TCOD_LEFT,
							mod->effect->getDescription());
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
					armor->rarity.color * Gui::RARITY_COLOR_MULTIPLIER,
					TCOD_LEFT,
					armor->name);
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					Gui::FRAME_FG,
					TCOD_RIGHT,
					engine::string.defence(armor->defence));
				//mods
				for (auto &mod : armor->rarityMods){
					offsetY += 1;
					frame.printString(
						bounds.start.x + 1, bounds.start.y + offsetY,
						bounds.getWidth(), 0,
						Gui::FRAME_FG, TCOD_LEFT,
						mod->effect->getDescription());
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

