#pragma once
#include "LogFrame.h"
#include "InventoryFrame.h"
#include "EquipmentFrame.h"
#include "HelpFrame.h"
#include "QuestFrame.h"
#include "ItemPickFrame.h"

class Gui
{
public:
	LogFrame log = LogFrame("", true, 1.0, 0.3);
	InventoryFrame inventory = InventoryFrame("Inventory", false, 1.0, 1.0);
	EquipmentFrame equipment = EquipmentFrame("Equipment", false, 1.0, 1.0);
	QuestFrame quest = QuestFrame("Quest", true, 1.0, 1.0);
	HelpFrame help = HelpFrame("Help", false, 1.0, 1.0);

	ItemPickFrame pickFrame = ItemPickFrame("Items", false, 1.0, 1.0);
	
	void render(float elapsed);
	bool handleKey(TCOD_key_t key);

	Gui(){};
};

