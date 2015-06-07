
#include "libtcod.hpp"
#include "Engine.h"

// Hide console window
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


int main(int argc, char* argv[])
{
	TCODConsole::initRoot(120, 60, "Roguelike", false);

	Engine engine = Engine();
	engine.start();

	return 0;
}