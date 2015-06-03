#pragma once
#include "libtcod.hpp"
#include "memory"
class Log
{
public:
	bool isOpen;

	std::shared_ptr<TCODConsole> console;

	void init();

	void openOrClose();

	void render();

	Log(){};
};

