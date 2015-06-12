#pragma once
#include "GuiFrame.h"
class InspectionFrame : public GuiFrame
{
private:
	const TCODColor inspectorColor = TCODColor::green;
public:
	Point2D inspectorLocation;
	
	void GuiFrame::render(float elapsed);
	bool handleKey(TCOD_key_t key);

	void onOpen();

	InspectionFrame(std::string name, char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(name, controlKey, open, alphaFg, alphaBg){};
};

