#include "StatisticsFrame.h"
#include "Engine.h"
#include "String.h"

void StatisticsFrame::render(){
	GuiFrame::render();

	int healthCurrent = engine::playerHandler.getPlayerCreature()->health;
	int healthMax = engine::playerHandler.getPlayerCreature()->healthMax;
	float percentage = ((float)healthCurrent / (float)healthMax);
	TCODColor healthColor = TCODColor::lerp(HEALTH_MIN_COLOR, HEALTH_MAX_COLOR, percentage);

	printString(0, 0, getWidth(), getHeight(), FG_COLOR, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, "Health");
	printString(0, 0, getWidth(), getHeight(), healthColor, healthColor, TCOD_CENTER, TCOD_BKGND_NONE, engine::string.outOf(healthCurrent, healthMax));

	blit();
}

bool StatisticsFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	return handled;
}