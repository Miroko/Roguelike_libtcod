#pragma once
#include "GuiFrame.h"
#include <vector>
#include <memory>

class DynamicObject;
class CreatureSkill;
class CreatureAction;
class ActionExecutionFrame : public GuiFrame
{
private:
	CreatureSkill *selectedSkill;
	CreatureAction *selectedAction;
	std::vector<std::shared_ptr<DynamicObject>> attackableObjects;
	std::shared_ptr<DynamicObject> previousTarget;
	int selectedObjectIndex;

	Rectangle gameObjectDisplayBounds;

	void executeSelectedAction();
	bool validSelectedSkillAction();

public:
	void updateAttackableObjects();
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);
	void update();
	void onOpen();
	void init(Rectangle &bounds);

	void setSkillAndAction(CreatureSkill &skill, CreatureAction &action);

	ActionExecutionFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg){};
};

