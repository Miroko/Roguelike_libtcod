#include "QuestFrame.h"
#include "Engine.h"
#include "Quest.h"

void QuestFrame::render(){
	GuiFrame::render();

	//Title
	console->printRectEx(console->getWidth()/2, 2, console->getWidth() - 1, 1, TCOD_BKGND_NONE, TCOD_CENTER, engine::questHandler.getCurrentQuest()->name.c_str());

	//Text
//	console->printRect(1, 4, console->getWidth() - 1, console->getHeight() - 4, engine::questHandler.getCurrentQuest()->getCurrentPhase()->description.c_str());

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