#pragma once
#include "libtcod.hpp"
#include "GuiComponent.h"
#include <vector>
#include <memory>
#include <string>
#include <functional>

class CreatureSkill;
class GuiSelectableSkillList : public GuiComponent
{
public:
	std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies;

	int selectedItemIndex = 0;
	int selectedOperation = 0;
	std::vector<std::string> operationsForSelectedItem;
	std::function<std::vector<std::string>(CreatureSkill*, bool selected)> getOperationsFunction;
	std::function<void(CreatureSkill*, double profiency, std::string)> onOperationSelectedFunction;

	void setSkillsAndProfiencies(std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies);
	void setGetOperationsFunction(std::function<std::vector<std::string>(CreatureSkill*, bool selected)> getOperations);
	void setOnOperationSelectedFunction(std::function<void(CreatureSkill*, double profiency, std::string)> onOperationSelected);
	bool handleKey(TCOD_key_t &key);
	void updateSelection();
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiSelectableSkillList() : GuiComponent(){};
};

