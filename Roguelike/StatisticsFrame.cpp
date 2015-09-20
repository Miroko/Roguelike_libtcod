#include "StatisticsFrame.h"
#include "Engine.h"
#include "String.h"
#include "Engine.h"

void StatisticsFrame::render(){
	GuiFrame::render();
	engine::playerHandler.getPlayerCreature()->renderToFrame(*this, creatureBounds);
	blit();
}

bool StatisticsFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	return handled;
}

void StatisticsFrame::init(Rectangle &bounds){
	GuiFrame::init(bounds);
	creatureBounds = Rectangle(getWidth(), getHeight());
}