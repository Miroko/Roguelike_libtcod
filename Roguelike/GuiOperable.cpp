#include "GuiOperable.h"
#include "OperatableObject.h"
#include "Gui.h"

void GuiOperable::setCurrentOperatable(OperatableObject &operatble){
	currentOperatable = &operatble;
}
void GuiOperable::render(){
	GuiFrame::render();
	if (currentOperatable != nullptr){
		printString(0, 0, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_LEFT, TCOD_BKGND_NONE,
			currentOperatable->getDescription());
	}
	blit();
}
