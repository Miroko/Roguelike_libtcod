#pragma once
#include "GuiFrame.h"
#include "PointerContainer.h"

class SelectableItemFrame : public GuiFrame
{

public:
	TCODColor selectionColor = TCODColor::lighterGreen;

	int selectedRow = 0;

	PointerContainer<Item> items;

	bool GuiFrame::handleKey(TCOD_key_t key);
	void GuiFrame::render(float elapsed);
	void openClose();

	virtual void onItemSelect(std::shared_ptr<Item> item) = 0;

	SelectableItemFrame(std::string name, bool open, float alphaFg, float alphaBg) : GuiFrame(name, open, alphaFg, alphaBg){};
};

