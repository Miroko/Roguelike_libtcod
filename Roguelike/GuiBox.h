#pragma once
#include "GuiComponent.h"
#include <string>

class GuiBox : public GuiComponent
{
public:
	std::string title;
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiBox(std::string title = "") :
		GuiComponent(), title(title){}
};
