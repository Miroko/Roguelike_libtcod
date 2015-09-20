#pragma once
#include "libtcod.hpp"
#include "GuiComponent.h"
#include <vector>
#include <memory>
#include <string>
#include <functional>

class CreatureSkill;
class CreatureAction;
class GuiSelectableActionList : public GuiComponent
{
public:
	CreatureSkill *selectedSkill;
	std::vector<std::pair<CreatureAction*, double>> actionsAndProfiencies;

	int selectedItemIndex = 0;
	int selectedOperation = 0;
	std::vector<std::string> operationsForSelectedItem;
	std::function<std::vector<std::string>(CreatureAction *action, bool selected)> getOperationsFunction;
	std::function<void(CreatureSkill *skill, CreatureAction *action, std::string)> onOperationSelectedFunction;

	void setActionsAndProfiencies(CreatureSkill &skill, std::vector<std::pair<CreatureAction*, double>> actionsAndProfiencies);
	void setGetOperationsFunction(std::function<std::vector<std::string>(CreatureAction *action, bool selected)> getOperations);
	void setOnOperationSelectedFunction(std::function<void(CreatureSkill *skill, CreatureAction *action, std::string)> onOperationSelected);
	bool handleKey(TCOD_key_t &key);
	void updateSelection();
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiSelectableActionList() : GuiComponent(){};
};

