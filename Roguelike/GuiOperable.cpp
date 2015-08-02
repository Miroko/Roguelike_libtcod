#include "GuiOperable.h"
#include "OperatableObject.h"
#include "Gui.h"
#include "GuiFrame.h"
#include "Engine.h"

void GuiOperable::setCurrentOperatable(OperatableObject *operatble){
	currentOperatable = operatble;
}
void GuiOperable::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (currentOperatable != nullptr){
		int offsetY = 0;
		frame.printString(
			bounds.start.x, bounds.start.y,
			bounds.getWidth(), 0, 
			Gui::FRAME_FG, 
			TCOD_CENTER, 
			currentOperatable->getDescription());
		offsetY += 2;
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_LEFT,
			"Durability");
		frame.printString(
			bounds.start.x, bounds.start.y + offsetY,
			bounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_RIGHT,
			engine::string.outOf(currentOperatable->health, currentOperatable->healthMax));
	}
}
