#pragma once
#include "GuiFrame.h"

class InspectionFrame : public GuiFrame
{
public:
	Point2D inspectorLocation;
	
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);
	void updateSelection();

	void onClose();
	void onOpen();

	InspectionFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Inspection"){};
};

