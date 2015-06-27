#include "QuestFrame.h"
#include "Engine.h"

void QuestFrame::render(){
	GuiFrame::render();

	//Title
	console->printRectEx(console->getWidth()/2, 2, console->getWidth() - 1, 1, TCOD_BKGND_NONE, TCOD_CENTER, Engine::questHandler.currentQuest->name.c_str());

	//Text
	console->printRect(1, 4, console->getWidth() - 1, console->getHeight() - 4, Engine::questHandler.currentQuest->currentPhase->description.c_str());

	blit();
}

bool QuestFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	bool handled = GuiFrame::handleKey(key, requireUpdate);
	if (!handled && isOpen){
		close();
		handled = true;
	}
	return handled;
}