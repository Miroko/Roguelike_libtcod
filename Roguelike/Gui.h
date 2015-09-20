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
#include "ActionExecutionFrame.h"
#include "SkillFrame.h"
#include "ActionFrame.h"
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
	static double INSPECTION_CURSOR_ALPHA;
	static double RARITY_COLOR_MULTIPLIER;
	static TCODColor HEALTH_MAX_COLOR;
	static TCODColor HEALTH_MIN_COLOR;
	static TCODColor STAMINA_MAX_COLOR;
	static TCODColor STAMINA_MIN_COLOR;
	static TCODColor MAGIC_MAX_COLOR;
	static TCODColor MAGIC_MIN_COLOR;

	LogFrame log = LogFrame(KEY_LOG, true, 1.0f, 1.0f);
	InventoryFrame inventory = InventoryFrame(KEY_INVENTORY, false, 1.0f, 1.0f);
	QuestFrame quest = QuestFrame(KEY_QUEST, false, 1.0f, 1.0f);
	HelpFrame help = HelpFrame(KEY_HELP, false, 1.0f, 1.0f);
	InspectionFrame inspection = InspectionFrame(KEY_INSPECT, false, 1.0f, 1.0f);
	ItemPickFrame pickFrame = ItemPickFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);
	StatisticsFrame statistics = StatisticsFrame(KEY_STATISTICS, true, 1.0f, 1.0f);
	DialogFrame dialog = DialogFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);
	TradeFrame trade = TradeFrame(KEY_UNDEFINED, false, 1.0f, 1.0f);
	ActionExecutionFrame attack = ActionExecutionFrame(KEY_ATTACK, false, 1.0f, 1.0f);
	SkillFrame skill = SkillFrame(KEY_SKILL, false, 1.0, 1.0);
	ActionFrame action = ActionFrame(KEY_UNDEFINED, false, 1.0, 1.0);

	void init();
	
	void render();
	bool handleKey(TCOD_key_t &key);
	void update();

	Gui(){};
};

