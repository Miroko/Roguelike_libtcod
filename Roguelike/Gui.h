#pragma once
#include "LogFrame.h"
#include "InventoryFrame.h"
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
	static int FRAME_MARGIN;
	static TCODColor FRAME_BG;
	static TCODColor FRAME_FG;
	static TCODColor SELECTABLE_BG;
	static TCODColor SELECTABLE_OPERATION;
	static TCODColor TRADE_SELECTED;
	static TCODColor INSPECTION_CURSOR;
	static float INSPECTION_CURSOR_ALPHA;
	static float RARITY_COLOR_MULTIPLIER;

	LogFrame log = LogFrame(KEY_LOG, true, 1.0f, 1.0f);
	InventoryFrame inventory = InventoryFrame(KEY_INVENTORY, false, 1.0f, 1.0f);
	QuestFrame quest = QuestFrame(KEY_QUEST, false, 1.0f, 1.0f);
	HelpFrame help = HelpFrame(KEY_HELP, false, 1.0f, 1.0f);
	InspectionFrame inspection = InspectionFrame(KEY_INSPECT, false, 1.0f, 1.0f);
	ItemPickFrame pickFrame = ItemPickFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);
	StatisticsFrame statistics = StatisticsFrame(KEY_STATISTICS, false, 1.0f, 1.0f);
	DialogFrame dialog = DialogFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);
	TradeFrame trade = TradeFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);
	AttackFrame attack = AttackFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);

	void init();
	
	void render();
	bool handleKey(TCOD_key_t &key);
	void update();

	Gui(){};
};

