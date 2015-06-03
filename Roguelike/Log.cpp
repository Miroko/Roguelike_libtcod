#include "Log.h"

void Log::init(){
	isOpen = false;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(TCODConsole::root->getWidth(), TCODConsole::root->getHeight()));
}

void Log::openOrClose(){
	isOpen = !isOpen;
}

void Log::render(){
	console->setDefaultBackground(TCODColor::lightRed);
	console->clear();
	TCODConsole::blit(console.get(), 0, 0, console->getWidth(), console->getHeight(), TCODConsole::root, 0, console->getHeight() * 0.75);
}