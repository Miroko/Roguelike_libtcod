#pragma once
#include "GuiFrame.h"
#include "KeyMapping.h"

class OperatableObject;
class GuiOperable : public GuiFrame
{
public:
	OperatableObject *currentOperatable = nullptr;

	void setCurrentOperatable(OperatableObject &operatable);
	void GuiFrame::render();

	GuiOperable() : GuiFrame(KEY_UNDEFINED, false){};
};

