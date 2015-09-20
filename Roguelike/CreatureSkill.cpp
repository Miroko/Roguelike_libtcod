#include "CreatureSkill.h"
#include "GuiFrame.h"
#include "Gui.h"
#include "Engine.h"

bool CreatureSkill::isType(CreatureSkill::Type type){
	return this->type == type;
}

std::vector<std::pair<CreatureAction*, double>> CreatureSkill::getActionsAndProficiencies(double skillProficiency){
	std::vector<std::pair<CreatureAction*, double>> actionsAndProfiencies;
	for (auto &action : actions){
		actionsAndProfiencies.push_back(std::make_pair(action.get(), action->profiencyModifier * skillProficiency));
	}
	return actionsAndProfiencies;
}

void CreatureSkill::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	frame.printString(
		renderBounds.start.x, renderBounds.start.y,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getDescription());
}

void CreatureSkill::renderToFrameLine(GuiFrame &frame, Rectangle &renderBounds, int offsetY){
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		getDescription());
}

std::string CreatureSkill::getStatistics(){
	return "";
}

std::string CreatureSkill::getDescription(){
	return name;
}