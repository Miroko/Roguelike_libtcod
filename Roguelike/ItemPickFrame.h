#pragma once
#include "GuiSelectableItemList.h"
#include "GuiItemDisplay.h"
#include "GuiBox.h"
#include "GuiFrame.h"

class ItemPickFrame : public GuiFrame
{
private:
	const std::vector<std::string> PICK_OPERATIONS = std::vector<std::string>({ "Take" });

	Rectangle guiDisplayBoxBounds;
	GuiBox guiDisplayBox;

	Rectangle guiItemDisplayBounds;
	GuiItemDisplay guiItemDisplay;

	Rectangle guiSelectableItemListBounds;
	GuiSelectableItemList guiSelectableItemList;

public:
	bool moveToInventory(std::shared_ptr<Item> &item);
	bool handleKey(TCOD_key_t &key);
	void init(Rectangle bounds);
	void render();
	void onOpen();
	void onClose();

	ItemPickFrame(char controlKey, bool open, float alphaFg, float alphaBg) : 
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Items"),
		guiDisplayBox("Items"){};
};

