#pragma once
#include "libtcod.hpp"
#include "GuiFrame.h"
#include "GuiSelectableActionList.h"
#include "GuiBox.h"

class CreatureAction;
class ActionFrame : public GuiFrame
{
private:
	const std::string USE = "Use";
	const std::vector<std::string> ACTION_OPERATIONS = std::vector<std::string>({ USE });

	CreatureAction *selectedAction = nullptr;

	Rectangle displayBoxBounds;
	GuiBox displayBox;

	Rectangle skillDisplayBounds;

	Rectangle selectableActionListBounds;
	GuiSelectableActionList selectableActionList;

public:
	void render();
	bool handleKey(TCOD_key_t &key);
	void init(Rectangle bounds);

	void setActionsAndProfiencies(CreatureSkill &selectedSkill, std::vector<std::pair<CreatureAction*, double>> actionsAndProfiencies);

	ActionFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Skill Actions"){};
};

