#include "GuiCreature.h"
#include "Creature.h"
#include "Engine.h"
#include "Weapon.h"

void GuiCreature::setCurrentCreature(Creature &creature){
	currentCreature = &creature;
}
void GuiCreature::render(){
	GuiFrame::render();
	if (currentCreature != nullptr){

		//rarity + name
		printString(0, 0, getWidth(), 1, currentCreature->rarity.color, BG_COLOR, TCOD_CENTER, TCOD_BKGND_NONE, currentCreature->rarity.name + " " + currentCreature->name);

		//health
		float percentage = ((float)currentCreature->health / (float)currentCreature->healthMax);
		TCODColor healthColor = TCODColor::lerp(HEALTH_MIN_COLOR, HEALTH_MAX_COLOR, percentage);

		printString(0, 2, getWidth(), getHeight(), FG_COLOR, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, "Health");
		printString(0, 2, getWidth(), getHeight(), healthColor, healthColor, TCOD_CENTER, TCOD_BKGND_NONE, engine::string.outOf(currentCreature->health, currentCreature->healthMax));

		//mods
		int offsetY = 4;
		for (auto &mod : currentCreature->rarityMods){
			printString(0, offsetY, getWidth(), 1, currentCreature->rarity.color, BG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, mod->name);
			++offsetY;
			//effects
			for (auto &effect : mod->effects){
				printString(1, offsetY, getWidth(), 1, FG_COLOR, BG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, "-" + effect->getDescription());
				++offsetY;
			}
		}
		//weapon
		if (currentCreature->inventory.currentWeapon != nullptr){
			printString(0, offsetY + 2, getWidth(), 1, FG_COLOR, BG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE,
				"Wielding ");
			printString(0, offsetY + 3, getWidth(), 1, currentCreature->inventory.currentWeapon->rarity.color, BG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE,
				currentCreature->inventory.currentWeapon->getDescription());
			printString(0, offsetY + 3, getWidth(), 1, FG_COLOR, BG_COLOR, TCOD_RIGHT, TCOD_BKGND_NONE,
				currentCreature->inventory.currentWeapon->getStatistics());
			for (auto &mod : currentCreature->inventory.currentWeapon->rarityMods){
				printString(0, offsetY + 4, getWidth(), 1, currentCreature->inventory.currentWeapon->rarity.color, BG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, mod->name);
				++offsetY;
				//effects
				for (auto &effect : mod->effects){
					printString(1, offsetY + 4, getWidth(), 1, FG_COLOR, BG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, "-" + effect->getDescription());
					++offsetY;
				}
			}
		}
	}
	blit();
}

