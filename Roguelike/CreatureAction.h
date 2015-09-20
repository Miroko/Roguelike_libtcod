#pragma once
#include "GuiObject.h"
#include <string>

class Creature;
class GameObject;
class DynamicObject;
class CreatureAction : public GuiObject
{
public:	
	std::string name;
	std::string logDescription;
	double profiencyModifier;
	int range;

	//return true if executed successfully
	virtual bool execute(Creature &executer, double profiencyModifier, GameObject &actionObject, DynamicObject &target) = 0;

	virtual std::string GuiObject::getStatistics() override;
	virtual std::string GuiObject::getDescription() override;
	virtual void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;
	virtual void GuiObject::renderToFrameLine(GuiFrame &frame, Rectangle &bounds, int offsetY) override;

	CreatureAction(std::string name, std::string logDescription, double profiencyModifier, int range) :
		GuiObject(),
		name(name),
		logDescription(logDescription),
		profiencyModifier(profiencyModifier),
		range(range){}
	CreatureAction(){}
};

