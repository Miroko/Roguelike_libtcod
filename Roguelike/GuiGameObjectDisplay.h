#pragma once
#include "GuiComponent.h"

class GameObject;
class GuiGameObjectDisplay : public GuiComponent
{
private:
	GameObject *objectInDisplay;

public:
	void setDisplayedObject(GameObject *object);
	void clear();

	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiGameObjectDisplay() : GuiComponent(){};
};

