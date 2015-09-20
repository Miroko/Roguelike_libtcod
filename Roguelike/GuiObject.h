#pragma once
#include <string>

class Rectangle;
class GuiFrame;
class GuiObject
{
public:
	virtual std::string getStatistics() = 0;
	virtual std::string getDescription() = 0;
	virtual void renderToFrame(GuiFrame &frame, Rectangle &renderBounds) = 0;
	virtual void renderToFrameLine(GuiFrame &frame, Rectangle &bounds, int offsetY) = 0;

	GuiObject(){};
};

