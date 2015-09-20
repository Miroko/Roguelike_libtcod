#pragma once
#include "DynamicObject.h"

class OperatableObject : public DynamicObject
{
public:
	bool isOn = false;

	virtual void on();
	virtual void off();

	virtual bool passable(DynamicObject &dynamicObject);

	void onTakeDamageEffect();
	void messageDeath();

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	virtual std::shared_ptr<OperatableObject> copy();

	OperatableObject(DynamicObject dynamicObject) :
		DynamicObject(dynamicObject){}
};
