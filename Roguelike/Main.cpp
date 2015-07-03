#include "libtcod.hpp"
#include "Engine.h"

// Hide console window
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char* argv[])
{
	engine::init();
	return 0;
}