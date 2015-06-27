#include "Gui.h"

void Gui::init(){
	log.init(Rectangle(Point2D(0, TCODConsole::root->getHeight() - 12),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	inventory.init(Rectangle(Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 2 - 10, TCODConsole::root->getHeight())));

	equipment.init(Rectangle(Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 2 - 10, TCODConsole::root->getHeight())));

	quest.init(Rectangle(Point2D(TCODConsole::root->getWidth() / 7, TCODConsole::root->getHeight() / 9),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 7, TCODConsole::root->getHeight() - TCODConsole::root->getHeight() / 9)));

	help.init(Rectangle(Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	inspection.init(Rectangle(Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getWidth() / 4)));

	pickFrame.init(Rectangle(Point2D(TCODConsole::root->getWidth() / 3, TCODConsole::root->getHeight() / 5),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 3, TCODConsole::root->getHeight() - TCODConsole::root->getHeight() / 5)));

	statistics.init(Rectangle(Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getWidth() / 4)));

	dialog.init(Rectangle(Point2D(TCODConsole::root->getWidth() / 2 - 30, 2),
		Point2D(TCODConsole::root->getWidth() / 2 + 30, TCODConsole::root->getHeight() - 2)));

	trade.init(Rectangle(Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	attack.init(Rectangle(Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getWidth() / 4)));

}

bool Gui::handleKey(TCOD_key_t key, bool &requireUpdate){	
	bool handled = false;
	if (inventory.handleKey(key, requireUpdate)) handled = true;
	if (equipment.handleKey(key, requireUpdate)) handled = true;
	if (quest.handleKey(key, requireUpdate)) handled = true;
	if (help.handleKey(key, requireUpdate)) handled = true;
	if (log.handleKey(key, requireUpdate)) handled = true;
	if (pickFrame.handleKey(key, requireUpdate)) handled = true;
	if (inspection.handleKey(key, requireUpdate)) handled = true;
	if (statistics.handleKey(key, requireUpdate)) handled = true;
	if (trade.handleKey(key, requireUpdate)) handled = true;
	if (dialog.handleKey(key, requireUpdate)) handled = true;
	if (attack.handleKey(key, requireUpdate)) handled = true;
	return handled;
}

void Gui::render(){
	if (inspection.isOpen) inspection.render();
	if (attack.isOpen) attack.render();
	if (log.isOpen) log.render();
	if (statistics.isOpen) statistics.render();
	if (inventory.isOpen) inventory.render();
	if (equipment.isOpen) equipment.render();
	if (pickFrame.isOpen) pickFrame.render();
	if (quest.isOpen) quest.render();
	if (help.isOpen) help.render();
	if (dialog.isOpen) dialog.render();
	if (trade.isOpen) trade.render();
}
