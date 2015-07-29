#include "StatisticsFrame.h"
#include "Engine.h"
#include "String.h"
#include "Engine.h"

void StatisticsFrame::render(){
	GuiFrame::render();
	guiCreature.setCurrentCreature(engine::playerHandler.getPlayerCreature().get());
	guiCreature.renderTo(*this);
	blit();
}

bool StatisticsFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	return handled;
}