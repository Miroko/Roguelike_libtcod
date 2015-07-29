#pragma once

class GuiFrame;
class OperatableObject;
class GuiOperable
{
public:
	OperatableObject *currentOperatable = nullptr;

	void setCurrentOperatable(OperatableObject *operatable);
	void renderTo(GuiFrame &frame);

	GuiOperable(){};
};

