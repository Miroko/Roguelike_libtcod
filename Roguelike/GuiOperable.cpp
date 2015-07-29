#include "GuiOperable.h"
#include "OperatableObject.h"
#include "Gui.h"
#include "GuiFrame.h"

void GuiOperable::setCurrentOperatable(OperatableObject *operatble){
	currentOperatable = operatble;
}
void GuiOperable::renderTo(GuiFrame &frame){
	if (currentOperatable != nullptr){
		frame.printString(0, 0, frame.getWidth(), 1, Gui::FRAME_FG, TCOD_CENTER, currentOperatable->getDescription());
	}
}
