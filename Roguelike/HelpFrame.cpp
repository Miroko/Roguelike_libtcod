#include "HelpFrame.h"


bool HelpFrame::handleKey(TCOD_key_t key){
	return false;
}

void HelpFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	blit();
}