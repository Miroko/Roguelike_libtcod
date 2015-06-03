#include "Inventory.h"


void Inventory::init(){
	isOpen = false;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(TCODConsole::root->getWidth(), TCODConsole::root->getHeight()));
}

void Inventory::openOrClose(){
	isOpen = !isOpen;
}

void Inventory::render(){
	console->setDefaultBackground(TCODColor::lightRed);
	console->clear();
	TCODConsole::blit(console.get(), 0, 0, console->getWidth(), console->getHeight(), TCODConsole::root, TCODConsole::root->getWidth()/1.3, 0);
}