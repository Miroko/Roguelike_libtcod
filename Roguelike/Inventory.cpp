#include "Inventory.h"
#include "Engine.h"

bool Inventory::handleKey(TCOD_key_t key){

	return false;
}

void Inventory::render(float elapsed){
	GuiFrame::render(elapsed);
	
	char selectionLetter = 'a';
	int y = 1;
	for (auto &weapon : weapons.items){
		if (Engine::playerHandler.playerCreature->weapon == weapon.get()) continue; //Equipped not showing in inventory

		console->printRect(1, y, TCODConsole::root->getWidth(), 1,
			("(" + std::string(1, selectionLetter) + ") " + weapon->name + " " + std::to_string(weapon->damage)).c_str());

		y++;
		selectionLetter++;
	}

	blit();
}

void Inventory::equip(Weapon &weapon){
	Engine::playerHandler.playerCreature->weapon = &weapon;
}

void Inventory::unEquip(Equipment *slot){
	slot = nullptr;
}