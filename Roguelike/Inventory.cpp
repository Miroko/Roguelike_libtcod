#include "Inventory.h"

void Inventory::init(){
	loot.weapons.push_back(Sword());
	isOpen = false;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(TCODConsole::root->getWidth(), TCODConsole::root->getHeight()));
}

void Inventory::openOrClose(){
	isOpen = !isOpen;
}

void Inventory::render(){
	console->printFrame(0, 0, console->getWidth(), console->getHeight());
	
	char selectionLetter = 'a';
	int y = 1;
	for (Weapon &w : loot.weapons){		
		console->printRect(1, y, TCODConsole::root->getWidth(), 1, ("(" + std::string(1, selectionLetter) + ") " + w.name).c_str());
		y++;
		selectionLetter++;
	}

	TCODConsole::blit(console.get(), 0, 0, console->getWidth(), console->getHeight(), TCODConsole::root, TCODConsole::root->getWidth()/1.3, 0);
}