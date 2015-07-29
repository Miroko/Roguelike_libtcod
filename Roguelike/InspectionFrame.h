#pragma once
#include "GuiFrame.h"
#include "GuiCreature.h"
#include "GuiTile.h"
#include "GuiOperable.h"
#include "GuiItemDisplay.h"

class InspectionFrame : public GuiFrame
{
private:
	Rectangle guiItemDisplayBounds;
	GuiItemDisplay guiItemDisplay;
	GuiCreature guiCreature;
	GuiTile guiTile;
	GuiOperable guiOperatable;

public:
	Point2D inspectorLocation;
	
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);
	void updateSelection();
	void init(Rectangle bounds);

	void onOpen();

	InspectionFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Inspection"){};
};

