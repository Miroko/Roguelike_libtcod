#include "GuiSelectableSkillList.h"
#include "GuiFrame.h"
#include "Gui.h"
#include "Direction.h"
#include "CreatureSkill.h"
#include "Engine.h"
#include <algorithm>

void GuiSelectableSkillList::setSkillsAndProfiencies(std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies){
	this->skillsAndProfiencies = skillsAndProfiencies;
	std::sort(this->skillsAndProfiencies.begin(), this->skillsAndProfiencies.end(), []
		(std::pair<CreatureSkill*, double> &a, std::pair<CreatureSkill*, double> &b){
		return a.second < b.second;
	});
	selectedItemIndex = 0;
	selectedOperation = 0;
	updateSelection();
}

void GuiSelectableSkillList::setGetOperationsFunction(std::function<std::vector<std::string>(CreatureSkill*, bool)> getOperations){
	getOperationsFunction = getOperations;
}

void GuiSelectableSkillList::setOnOperationSelectedFunction(std::function<void(CreatureSkill*, double profiency, std::string)> onOperationSelected){
	onOperationSelectedFunction = onOperationSelected;
}

bool GuiSelectableSkillList::handleKey(TCOD_key_t &key){
	bool handled = false;
	Point2D direction;
	if (!skillsAndProfiencies.empty()){
		direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == UP){
				if (selectedItemIndex == 0) selectedItemIndex = skillsAndProfiencies.size() - 1;
				else selectedItemIndex--;
				updateSelection();
				selectedOperation = 0;
				handled = true;
			}
			else if (direction == DOWN){
				if (selectedItemIndex == skillsAndProfiencies.size() - 1) selectedItemIndex = 0;
				else selectedItemIndex++;
				updateSelection();
				selectedOperation = 0;
				handled = true;
			}
			else if (direction == LEFT){
				if (selectedOperation == 0) selectedOperation = operationsForSelectedItem.size() - 1;
				else selectedOperation--;
				handled = true;
			}
			else if (direction == RIGHT){
				if (selectedOperation == operationsForSelectedItem.size() - 1) selectedOperation = 0;
				else selectedOperation++;
				handled = true;
			}
			else if (direction == CENTER){
				onOperationSelectedFunction(
					skillsAndProfiencies.at(selectedItemIndex).first,
					skillsAndProfiencies.at(selectedItemIndex).second, 
					operationsForSelectedItem[selectedOperation]);
				updateSelection();
				handled = true;
			}
		}
	}
	return handled;
}

void GuiSelectableSkillList::updateSelection(){
	if (!skillsAndProfiencies.empty()){
		if (selectedItemIndex > (int)(skillsAndProfiencies.size() - 1)){
			selectedItemIndex = skillsAndProfiencies.size() - 1;
		}
		operationsForSelectedItem = getOperationsFunction(skillsAndProfiencies.at(selectedItemIndex).first, true);
		if (selectedOperation > (int)(operationsForSelectedItem.size() - 1)) selectedOperation = 0;
	}
}

void GuiSelectableSkillList::renderTo(GuiFrame &frame, Rectangle &bounds){
	//No skills
	if (skillsAndProfiencies.empty()){
		frame.printString(
			bounds.start.x, bounds.start.y + bounds.getHeight() / 2,
			bounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_CENTER,
			"No skills");
	}
	else{
		//Skills
		int startIndex = selectedItemIndex;
		if (startIndex > (int)(skillsAndProfiencies.size() - bounds.getHeight() - 1)){
			startIndex = skillsAndProfiencies.size() - bounds.getHeight() - 1;
			if (startIndex < 0) startIndex = 0;
		}
		int endIndex = startIndex + bounds.getHeight();
		if (endIndex >(int)(skillsAndProfiencies.size() - 1)){
			endIndex = skillsAndProfiencies.size() - 1;
		}
		auto &iterator = skillsAndProfiencies.begin();
		std::advance(iterator, startIndex);
		int offsetY = 0;
		for (int index = startIndex; index <= endIndex; ++index){
			auto item = *iterator;
			item.first->renderToFrameLine(frame, bounds, offsetY);
			//profiency
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_CENTER,
				engine::string.percentageValue(item.second));
			//operator
			if (index == selectedItemIndex){
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					Gui::SELECTABLE_OPERATION,
					TCOD_RIGHT,
					operationsForSelectedItem.at(selectedOperation));
				//row bg
				frame.paintBg(bounds.start.x, bounds.start.y + offsetY, bounds.getWidth(), 0, Gui::SELECTABLE_BG);
			}
			else{
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					Gui::SELECTABLE_OPERATION,
					TCOD_RIGHT,
					getOperationsFunction(item.first, false).at(0));
			}
			++offsetY;
			++iterator;
		}
	}
}
