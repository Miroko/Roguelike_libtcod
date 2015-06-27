#pragma once
#include "LogFrame.h"
#include "InventoryFrame.h"
#include "EquipmentFrame.h"
#include "HelpFrame.h"
#include "QuestFrame.h"
#include "ItemPickFrame.h"
#include "InspectionFrame.h"
#include "StatisticsFrame.h"
#include "DialogFrame.h"
#include "TradeFrame.h"
#include "AttackFrame.h"
#include "KeyMapping.h"

class Gui
{
public:
	LogFrame log = LogFrame(KEY_LOG, true, 1.0, 0.3);
	InventoryFrame inventory = InventoryFrame(KEY_INVENTORY, false, 1.0, 1.0);
	EquipmentFrame equipment = EquipmentFrame(KEY_EQUIPMENT, false, 1.0, 1.0);
	QuestFrame quest = QuestFrame(KEY_QUEST, true, 1.0, 1.0);
	HelpFrame help = HelpFrame(KEY_HELP, false, 1.0, 1.0);
	InspectionFrame inspection = InspectionFrame(KEY_INSPECT, false, 1.0, 1.0);
	ItemPickFrame pickFrame = ItemPickFrame(UNDEFINED, false, 1.0, 1.0);
	StatisticsFrame statistics = StatisticsFrame(KEY_STATISTICS, true, 1.0, 1.0);
	DialogFrame dialog = DialogFrame(UNDEFINED, false, 1.0, 1.0);
	TradeFrame trade = TradeFrame(UNDEFINED, false, 1.0, 1.0);
	AttackFrame attack = AttackFrame(UNDEFINED, false, 1.0, 1.0);

	void init();
	
	void render();
	bool handleKey(TCOD_key_t key, bool &requireUpdate);

	Gui(){};
};

