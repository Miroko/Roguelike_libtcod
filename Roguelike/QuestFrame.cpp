#include "QuestFrame.h"
#include "Engine.h"

void QuestFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	Quest *currentQuest = Engine::questHandler.currentQuest;

	//Title
	console->printRectEx(console->getWidth()/2, 2, console->getWidth() - 1, 1, TCOD_BKGND_NONE, TCOD_CENTER, currentQuest->name.c_str());

	//Text
	console->printRect(1, 4, console->getWidth() - 1, console->getHeight()-4, currentQuest->currentPhase->description.c_str());

	blit();
}

bool QuestFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (!handled && isOpen){
		close();
		handled = true;
	}
	return handled;
}