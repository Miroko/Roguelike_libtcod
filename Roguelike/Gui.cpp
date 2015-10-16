#include "Gui.h"
#include "Engine.h"

int Gui::FRAME_MARGIN;
double Gui::RARITY_COLOR_MULTIPLIER;
TCODColor Gui::FRAME_BG;
TCODColor Gui::FRAME_FG;
TCODColor Gui::SELECTABLE_BG;
TCODColor Gui::SELECTABLE_OPERATION;
TCODColor Gui::TRADE_SELECTED;
TCODColor Gui::INSPECTION_CURSOR;
double Gui::INSPECTION_CURSOR_ALPHA;
TCODColor Gui::HEALTH_MAX_COLOR;
TCODColor Gui::HEALTH_MIN_COLOR;
TCODColor Gui::STAMINA_MAX_COLOR;
TCODColor Gui::STAMINA_MIN_COLOR;
TCODColor Gui::MAGIC_MAX_COLOR;
TCODColor Gui::MAGIC_MIN_COLOR;

void Gui::init(){
	//Definations
	//parameters
	FRAME_MARGIN = 1;
	FRAME_BG = TCODColor(200, 190, 140);
	FRAME_FG = TCODColor(35, 30, 25);
	SELECTABLE_BG = FRAME_BG * 0.8f;
	SELECTABLE_OPERATION = TCODColor(10,94,10);
	TRADE_SELECTED = SELECTABLE_BG * 1.4f;
	INSPECTION_CURSOR = TCODColor::green;
	INSPECTION_CURSOR_ALPHA = 0.2f;
	RARITY_COLOR_MULTIPLIER = 0.6f;
	HEALTH_MAX_COLOR = TCODColor::darkGreen;
	HEALTH_MIN_COLOR = TCODColor::darkRed;
	STAMINA_MAX_COLOR = TCODColor::darkCyan;
	STAMINA_MIN_COLOR = TCODColor::desaturatedCyan * 0.5;
	MAGIC_MAX_COLOR = TCODColor::darkHan;
	MAGIC_MIN_COLOR = TCODColor::desaturatedHan * 0.5;

	//frames
	log.init(Rectangle(
		Point2D(0, TCODConsole::root->getHeight() - 12),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	inventory.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - 12)));

	quest.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 7, TCODConsole::root->getHeight() / 9),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 7, TCODConsole::root->getHeight() - TCODConsole::root->getHeight() / 9)));

	help.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	inspection.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - 12)));

	pickFrame.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - 12)));

	statistics.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight() - 12)));

	dialog.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 2 - 30, 2),
		Point2D(TCODConsole::root->getWidth() / 2 + 30, TCODConsole::root->getHeight() - 2)));

	trade.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() - 1, TCODConsole::root->getHeight() - 1)));

	attack.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - 12)));

	skill.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - 12)));

	action.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - 12)));
}

bool Gui::handleKey(TCOD_key_t &key){
	bool handled = false;
	if (inventory.handleKey(key)) handled = true;	
	if (quest.handleKey(key)) handled = true;
	if (help.handleKey(key)) handled = true;
	if (log.handleKey(key)) handled = true;
	if (pickFrame.handleKey(key)) handled = true;
	if (inspection.handleKey(key)) handled = true;
	if (statistics.handleKey(key)) handled = true;
	if (trade.handleKey(key)) handled = true;
	if (dialog.handleKey(key)) handled = true;
	if (action.handleKey(key)) handled = true;
	if (skill.handleKey(key)) handled = true;

	if (!handled){
		if (attack.handleKey(key)) handled = true;
	}
	return handled;
}

void Gui::render(){
	if (log.isOpen) log.render();
	if (inspection.isOpen) inspection.render();
	if (attack.isOpen) attack.render();
	if (statistics.isOpen) statistics.render();
	if (inventory.isOpen) inventory.render();
	if (pickFrame.isOpen) pickFrame.render();
	if (quest.isOpen) quest.render();
	if (help.isOpen) help.render();
	if (dialog.isOpen) dialog.render();
	if (trade.isOpen) trade.render();
	if (skill.isOpen) skill.render();
	if (action.isOpen) action.render();
}

void Gui::update(){
	if (log.isOpen) log.update();
	if (attack.isOpen) attack.update();
}
