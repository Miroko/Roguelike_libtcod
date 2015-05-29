
#include "libtcod.hpp"
#include "Engine.h"

// Hide console window
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


int main(int argc, char* argv[])
{
	TCODConsole::initRoot(120, 60, "Roguelike", false);
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(100, 10);

	Engine().startMainLoop();
	
	return 0;

}