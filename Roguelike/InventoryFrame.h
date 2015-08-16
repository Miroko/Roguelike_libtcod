#pragma once
#include "libtcod.hpp"
#include "GuiFrame.h"
#include "GuiSelectableItemList.h"
#include "GuiBox.h"
#include "GuiGameObjectDisplay.h"

class InventoryFrame : public GuiFrame
{
private:
	const std::string EQUIP = "Equip";
	const std::string UNEQUIP = "Unequip";
	const std::string CONSUME = "Consume";
	const std::string DROP = "Drop";
	const std::vector<std::string> EQUIPMENT_UNEQUIP_OPERATIONS = std::vector<std::string>({ UNEQUIP, DROP });
	const std::vector<std::string> EQUIPMENT_EQUIP_OPERATIONS = std::vector<std::string>({ EQUIP, DROP });
	const std::vector<std::string> CONSUMABLE_OPERATIONS = std::vector<std::string>({ CONSUME, DROP });

	Rectangle guiTopBoxBounds;
	GuiBox guiTopBox;

	Rectangle guiDisplayBoxBounds;
	GuiBox guiDisplayBox;

	Rectangle guiGameObjectDisplayBounds;
	GuiGameObjectDisplay guiGameObjectDisplay;

	Rectangle guiSelectableItemListBounds;
	GuiSelectableItemList guiSelectableItemList;

public:
	void onOpen();
	void render();
	bool handleKey(TCOD_key_t &key);
	void init(Rectangle bounds);

	InventoryFrame(char controlKey, bool open, double alphaFg, double alphaBg) : 
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Inventory"),
		guiTopBox("Inventory"){};
};
