#include "GuiCreature.h"
#include "Creature.h"
#include "Engine.h"
#include "Weapon.h"
#include "Armor.h"
#include "GuiFrame.h"

void GuiCreature::setCurrentCreature(Creature *creature){
	currentCreature = creature;
}
void GuiCreature::renderTo(GuiFrame &frame){
	if (currentCreature != nullptr){
		int offsetY = 0;
		//Creature
		//rarity
		frame.printString(0, offsetY, frame.getWidth(), 1, currentCreature->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, TCOD_CENTER, currentCreature->rarity.name);
		offsetY += 1;
		frame.printString(0, offsetY, frame.getWidth(), 1, currentCreature->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, TCOD_CENTER, currentCreature->name);
		//health
		offsetY += 2;
		float percentage = ((float)currentCreature->health / (float)currentCreature->healthMax);
		TCODColor healthColor = TCODColor::lerp(HEALTH_MIN_COLOR, HEALTH_MAX_COLOR, percentage);
		frame.printString(0, offsetY, frame.getWidth(), frame.getHeight(), Gui::FRAME_FG, TCOD_LEFT, "Health");
		frame.printString(0, offsetY, frame.getWidth(), frame.getHeight(), healthColor, TCOD_CENTER, engine::string.outOf(currentCreature->health, currentCreature->healthMax));
		//mods
		for (auto &mod : currentCreature->rarityMods){
			offsetY += 1;
			frame.printString(1, offsetY, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_LEFT, mod->effect->getDescription());
		}

		//Equipment
		offsetY += 2;
		frame.printString(0, offsetY, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_LEFT, "Equipment ");
		//weapon
		if (currentCreature->inventory.currentWeapon != nullptr){
			offsetY += 1;
			frame.printString(0, offsetY, frame.getWidth(), 1, currentCreature->inventory.currentWeapon->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, TCOD_LEFT, currentCreature->inventory.currentWeapon->name);
			frame.printString(0, offsetY, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_RIGHT, engine::string.damage(currentCreature->inventory.currentWeapon->damage));
			//mods
			for (auto &mod : currentCreature->inventory.currentWeapon->rarityMods){
				offsetY += 1;
				frame.printString(1, offsetY, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_LEFT, mod->effect->getDescription());
			}
		}
		//armors
		for (auto &limb : currentCreature->limbs){
			if (limb.currentArmor != nullptr){
				offsetY += 1;
				frame.printString(0, offsetY, frame.getWidth(), 1, limb.currentArmor->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, TCOD_LEFT, limb.currentArmor->name);
				frame.printString(0, offsetY, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_RIGHT, engine::string.defence(limb.currentArmor->defence));
				//mods
				for (auto &mod : limb.currentArmor->rarityMods){
					offsetY += 1;
					frame.printString(1, offsetY, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_LEFT, mod->effect->getDescription());
				}
			}
		}
	}
}

