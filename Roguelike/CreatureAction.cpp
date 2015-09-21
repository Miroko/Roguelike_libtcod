#include "CreatureAction.h"
#include "GuiFrame.h"
#include "Gui.h"
#include "Engine.h"

bool CreatureAction::execute(Creature &executer, double profiencyModifier, GameObject &actionObject, DynamicObject &target){
	engine::visualEffectPlayer.playEffect(target.location, visualEffectOnExecution);
	return true;
}

void CreatureAction::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	frame.printString(
		renderBounds.start.x, renderBounds.start.y,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getDescription());
}

void CreatureAction::renderToFrameLine(GuiFrame &frame, Rectangle &renderBounds, int offsetY){
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		getDescription());
}

std::string CreatureAction::getStatistics(){
	return "";
}

std::string CreatureAction::getDescription(){
	return name;
}
