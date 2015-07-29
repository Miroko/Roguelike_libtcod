#pragma once

class Rectangle;
class GuiFrame;
class GuiComponent
{
public:
	virtual void renderTo(GuiFrame &frame, Rectangle &bounds) = 0;

	GuiComponent(){};
};
