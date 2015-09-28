#include "OperatableObject.h"
#include "Engine.h"

void OperatableObject::operate(Creature &user){
	engine::visualEffectPlayer.playEffect(location, visualEffectOnOperate);
}

void OperatableObject::messageDeath(){
	engine::gui.log.finishMessage(name + " is destroyed.");
}

bool OperatableObject::isPassable(DynamicObject &dynamicObject){
	return DynamicObject::isPassable(dynamicObject);
}

void OperatableObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	int offsetY = 0;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getDescription());
	offsetY += 2;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		"Durability");
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_RIGHT,
		engine::string.outOf(getHealthCurrent(), getHealthMax()));
}

std::shared_ptr<OperatableObject> OperatableObject::copy(){
	return std::shared_ptr<OperatableObject>(new OperatableObject(*this));
}