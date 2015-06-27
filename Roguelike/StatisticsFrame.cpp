#include "StatisticsFrame.h"
#include "Engine.h"

void StatisticsFrame::render(){
	GuiFrame::render();

	console->printRectEx(1, 2, console->getWidth() - 1, 1, TCOD_BKGND_NONE, TCOD_LEFT, "Health: ");

	int healthCurrent = Engine::playerController.playerCreature->health;
	int healthMax = Engine::playerController.playerCreature->healthMax;
	
	float percentage = ((float)healthCurrent / (float)healthMax);
	TCODColor healthColor = TCODColor::lerp(healthMinColor, healthMaxColor, percentage);

	std::string healthString = "(" + std::to_string(healthCurrent) + "/" + std::to_string(healthMax) + ")";

	console->setDefaultForeground(healthColor);
	console->printRectEx(console->getWidth()/2, 2, console->getWidth() - 1, 1, TCOD_BKGND_NONE, TCOD_CENTER, healthString.c_str());

	blit();
}

bool StatisticsFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	bool handled = GuiFrame::handleKey(key, requireUpdate);
	return handled;
}