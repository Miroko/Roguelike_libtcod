#pragma once
#include "GuiObject.h"
#include <memory>
#include <string>

class Creature;
class GameObject;
class DynamicObject;
class VisualEffect;
class CreatureAction : public GuiObject
{
private:
	std::shared_ptr<VisualEffect> visualEffectOnExecution;

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

	CreatureAction(std::string name, std::string logDescription, double profiencyModifier, int range, std::shared_ptr<VisualEffect> visualEffectOnExecution = nullptr) :
		GuiObject(),
		name(name),
		logDescription(logDescription),
		profiencyModifier(profiencyModifier),
		range(range),
		visualEffectOnExecution(visualEffectOnExecution){}
	CreatureAction(){}
};

