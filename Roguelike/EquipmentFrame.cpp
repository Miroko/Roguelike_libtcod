#include "EquipmentFrame.h"


void EquipmentFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	blit();
}

bool EquipmentFrame::handleKey(TCOD_key_t key){
	return false;
}