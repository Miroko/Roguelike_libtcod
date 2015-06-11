#pragma once
#include "LogFrame.h"
#include "InventoryFrame.h"
#include "EquipmentFrame.h"
#include "HelpFrame.h"
#include "QuestFrame.h"
#include "ItemPickFrame.h"
#include "KeyMapping.h"

class Gui
{
public:
	LogFrame log = LogFrame("", KEY_LOG, true, 1.0, 0.3);
	InventoryFrame inventory = InventoryFrame("Inventory", KEY_INVENTORY, false, 1.0, 1.0);
	EquipmentFrame equipment = EquipmentFrame("Equipment", KEY_EQUIPMENT, false, 1.0, 1.0);
	QuestFrame quest = QuestFrame("Quest", KEY_QUEST, true, 1.0, 1.0);
	HelpFrame help = HelpFrame("Help", KEY_HELP, false, 1.0, 1.0);

	ItemPickFrame pickFrame = ItemPickFrame("Items", KEY_TAKE, false, 1.0, 1.0);
	
	void render(float elapsed);
	bool handleKey(TCOD_key_t key);

	Gui(){};
};

