#pragma once
#include "GuiFrame.h"
#include "PointerContainer.h"
#include "Direction.h"
#include "KeyMapping.h"
#include <vector>

class SelectableItemFrame : public GuiFrame
{
protected:
	const TCODColor SELECTION_COLOR = TCODColor::darkestGreen;
	const TCODColor OPERATION_COLOR = TCODColor::lightRed;

	int selectedRow = 0;
	int selectedOperation = 0;
	std::vector<std::string> operations;

	virtual void onItemSelect(std::shared_ptr<Item> &item, std::string &operation) = 0;
	virtual std::vector<std::string> getOperationsForItem(std::shared_ptr<Item> &item) = 0;
	void renderSelection();

public:
	PointerContainer<Item> items;

	void addItem(std::shared_ptr<Item> &item);
	void removeItem(std::shared_ptr<Item> &item);
	void removeAll();
	void onOpen();

	void GuiFrame::render();

	bool handleKey(TCOD_key_t key, bool &requireUpdate);

	SelectableItemFrame(char controlKey, bool open, float alphaFg = 1.0, float alphaBg = 1.0, std::string title = "") :
		GuiFrame(controlKey, open, alphaFg, alphaBg, title){};
};

