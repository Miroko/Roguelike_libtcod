#pragma once
#include "Log.h"
#include "Inventory.h"
class Gui
{
public:
	Inventory inventory = Inventory("Inventory", false, 1.0, 1.0);
	Log log = Log("Log", true, 1.0, 0.3);

	Gui(){};
};

