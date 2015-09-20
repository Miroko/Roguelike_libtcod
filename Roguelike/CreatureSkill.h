#pragma once
#include "GuiObject.h"
#include <vector>
#include <memory>

class CreatureAction;
class CreatureSkill : public GuiObject
{
public:
	enum Type
	{
		MAGIC,
		WEAPON
	};

	bool isType(CreatureSkill::Type type);

	Type type;
	std::string name;
	std::vector<std::shared_ptr<CreatureAction>> actions;

	virtual std::string GuiObject::getStatistics() override;
	virtual std::string GuiObject::getDescription() override;
	virtual void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;
	virtual void GuiObject::renderToFrameLine(GuiFrame &frame, Rectangle &bounds, int offsetY) override;

	std::vector<std::pair<CreatureAction*, double>> getActionsAndProficiencies(double skillProficiency);

	CreatureSkill(Type type, std::string name, std::vector<std::shared_ptr<CreatureAction>> actions) :
		GuiObject(),
		type(type),
		name(name),
		actions(actions){}
};

