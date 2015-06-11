#include "HelpFrame.h"


bool HelpFrame::handleKey(TCOD_key_t key){
	GuiFrame::handleKey(key);
	if (!isOpen) return true;
	else if (key.pressed) close();
	return false;
}

void HelpFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	blit();
}