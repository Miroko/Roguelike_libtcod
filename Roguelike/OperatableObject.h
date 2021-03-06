#pragma once
#include "DynamicObject.h"
#include "RarityMod.h"

class Creature;
class OperatableObject : public DynamicObject, public RarityMod
{
private:	
	std::shared_ptr<VisualEffect> visualEffectOnOperate;

public:
	virtual void operate(Creature &user);

	virtual void messageDeath() override;
	virtual bool isPassable(DynamicObject &dynamicObject) override;

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	virtual std::shared_ptr<OperatableObject> copy();

	OperatableObject(DynamicObject dynamicObject, std::shared_ptr<VisualEffect> visualEffectOnOperate = nullptr) :
		DynamicObject(dynamicObject),
		visualEffectOnOperate(visualEffectOnOperate){}
};
