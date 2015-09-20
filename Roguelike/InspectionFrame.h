#pragma once
#include "GuiFrame.h"
#include "GuiGameObjectDisplay.h"

class InspectionFrame : public GuiFrame
{
private:
	Rectangle guiGameObjectDisplayBounds;
	GuiGameObjectDisplay guiGameObjectDisplay;

public:
	Point2D inspectorLocation;
	
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);
	void updateSelection();
	void init(Rectangle bounds);

	void onOpen();

	InspectionFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Inspection"){};
};

