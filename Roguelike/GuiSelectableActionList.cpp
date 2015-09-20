#include "GuiSelectableActionList.h"
#include "GuiFrame.h"
#include "Gui.h"
#include "Direction.h"
#include "CreatureSkill.h"
#include "Engine.h"
#include <algorithm>

void GuiSelectableActionList::setActionsAndProfiencies(CreatureSkill &skill, std::vector<std::pair<CreatureAction*, double>> actionsAndProfiencies){
	selectedSkill = &skill;
	this->actionsAndProfiencies = actionsAndProfiencies;
	std::sort(this->actionsAndProfiencies.begin(), this->actionsAndProfiencies.end(), []
		(std::pair<CreatureAction*, double> &a, std::pair<CreatureAction*, double> &b){
		return a.second < b.second;
	});
	selectedItemIndex = 0;
	selectedOperation = 0;
	updateSelection();
}

void GuiSelectableActionList::setGetOperationsFunction(std::function<std::vector<std::string>(CreatureAction *action, bool selected)> getOperations){
	getOperationsFunction = getOperations;
}

void GuiSelectableActionList::setOnOperationSelectedFunction(std::function<void(CreatureSkill *skill, CreatureAction *action, std::string)> onOperationSelected){
	onOperationSelectedFunction = onOperationSelected;
}

bool GuiSelectableActionList::handleKey(TCOD_key_t &key){
	bool handled = false;
	Point2D direction;
	if (!actionsAndProfiencies.empty()){
		direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == UP){
				if (selectedItemIndex == 0) selectedItemIndex = actionsAndProfiencies.size() - 1;
				else selectedItemIndex--;
				updateSelection();
				selectedOperation = 0;
				handled = true;
			}
			else if (direction == DOWN){
				if (selectedItemIndex == actionsAndProfiencies.size() - 1) selectedItemIndex = 0;
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
					selectedSkill,
					actionsAndProfiencies.at(selectedItemIndex).first,
					operationsForSelectedItem[selectedOperation]);
				updateSelection();
				handled = true;
			}
		}
	}
	return handled;
}

void GuiSelectableActionList::updateSelection(){
	if (!actionsAndProfiencies.empty()){
		if (selectedItemIndex > (int)(actionsAndProfiencies.size() - 1)){
			selectedItemIndex = actionsAndProfiencies.size() - 1;
		}
		operationsForSelectedItem = getOperationsFunction(actionsAndProfiencies.at(selectedItemIndex).first, true);
		if (selectedOperation > (int)(operationsForSelectedItem.size() - 1)) selectedOperation = 0;
	}
}

void GuiSelectableActionList::renderTo(GuiFrame &frame, Rectangle &bounds){
	//No actions
	if (actionsAndProfiencies.empty()){
		frame.printString(
			bounds.start.x, bounds.start.y + bounds.getHeight() / 2,
			bounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_CENTER,
			"No Actions");
	}
	else{
		//actions
		int startIndex = selectedItemIndex;
		if (startIndex > (int)(actionsAndProfiencies.size() - bounds.getHeight() - 1)){
			startIndex = actionsAndProfiencies.size() - bounds.getHeight() - 1;
			if (startIndex < 0) startIndex = 0;
		}
		int endIndex = startIndex + bounds.getHeight();
		if (endIndex >(int)(actionsAndProfiencies.size() - 1)){
			endIndex = actionsAndProfiencies.size() - 1;
		}
		auto &iterator = actionsAndProfiencies.begin();
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
