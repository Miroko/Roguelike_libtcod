#pragma once
#include "libtcod.hpp"
#include "GuiFrame.h"
#include "GuiSelectableSkillList.h"
#include "GuiBox.h"

class CreatureSkill;
class SkillFrame : public GuiFrame
{
private:
	const std::string USE = "Use";
	const std::vector<std::string> SKILL_OPERATIONS = std::vector<std::string>({ USE });

	CreatureSkill *selectedSkill = nullptr;

	Rectangle displayBoxBounds;
	GuiBox displayBox;

	Rectangle skillDisplayBounds;

	Rectangle selectableSkillListBounds;
	GuiSelectableSkillList selectableSkillList;

public:
	void onOpen();
	void render();
	bool handleKey(TCOD_key_t &key);
	void init(Rectangle bounds);

	void setSkillsAndProfiencies(std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies);

	SkillFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Skills"){};
};

