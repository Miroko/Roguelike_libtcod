#pragma once
#include "GuiFrame.h"
#include "PointerContainer.h"
#include "Direction.h"
#include "KeyMapping.h"
#include <vector>

class SelectableItemFrame : public GuiFrame
{
protected:
	TCODColor selectionColor = TCODColor::lighterGreen;

	int selectedRow = 0;

	std::vector<std::string> operations;
	int selectedOperation = 0;

public:
	PointerContainer<Item> items;

	bool handleKey(TCOD_key_t key);
	void GuiFrame::render(float elapsed);

	void addItem(std::shared_ptr<Item> &item);
	void removeItem(std::shared_ptr<Item> &item);
	void removeAll();
	void onOpen();

	virtual void onItemSelect(std::shared_ptr<Item> &item, std::string &operation) = 0;
	virtual std::vector<std::string> getOperationsForItem(std::shared_ptr<Item> &item) = 0;

	SelectableItemFrame(std::string name, char controlKey, bool open, float alphaFg = 1.0, float alphaBg = 1.0) : GuiFrame(name, controlKey, open, alphaFg, alphaBg){};
};

