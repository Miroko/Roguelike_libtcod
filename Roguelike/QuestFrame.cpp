#include "QuestFrame.h"


void QuestFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	console->printRect(1,console->getHeight()-2, console->getWidth(), 1, "Press 'q' to close");

	blit();
}

bool QuestFrame::handleKey(TCOD_key_t key){
	return false;
}