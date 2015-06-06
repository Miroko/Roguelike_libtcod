#include "Inventory.h"
#include "Engine.h"

void Inventory::init(bool open){
	isOpen = open;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(TCODConsole::root->getWidth(), TCODConsole::root->getHeight()));
}

void Inventory::openOrClose(){
	isOpen = !isOpen;
}

void Inventory::render(){
	console->setDefaultForeground(TCODColor::white);
	console->printFrame(0, 0, console->getWidth(), console->getHeight());

	console->setDefaultForeground(TCODColor::white);
	char selectionLetter = 'a';
	int y = 1;
	for (auto &weapon : weapons.items){		
		if (Engine::playerHandler.playerCreature->weapon == weapon.get()) continue; //Equipped not showing in inventory

		console->printRect(1, y, TCODConsole::root->getWidth(), 1,
			("(" + std::string(1, selectionLetter) + ") " + weapon->name + " " + std::to_string(weapon->damage)).c_str());

		y++;
		selectionLetter++;
	}

	TCODConsole::blit(console.get(), 0, 0, console->getWidth(), console->getHeight(), TCODConsole::root, TCODConsole::root->getWidth()/1.3, 0);
}

bool Inventory::handleKey(TCOD_key_t key){
	return false;
}

void Inventory::equip(Weapon &weapon){
	Engine::playerHandler.playerCreature->weapon = &weapon;
}

void Inventory::unEquip(Equipment *slot){
	slot = nullptr;
}