#pragma once
#include "GuiComponent.h"

class GuiFrame;
class OperatableObject;
class GuiOperable : public GuiComponent
{
public:
	OperatableObject *currentOperatable = nullptr;

	void setCurrentOperatable(OperatableObject *operatable);
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiOperable(){};
};

