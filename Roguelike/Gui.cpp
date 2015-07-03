#include "Gui.h"
#include "Engine.h"

void Gui::init(){
	log.init(Rectangle(
		Point2D(0, TCODConsole::root->getHeight() - 12),
		Point2D(TCODConsole::root->getWidth() - 1, TCODConsole::root->getHeight())));

	inventory.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 2 - 10, TCODConsole::root->getHeight() - 1)));

	quest.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 7, TCODConsole::root->getHeight() / 9),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 7, TCODConsole::root->getHeight() - TCODConsole::root->getHeight() / 9)));

	help.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	inspection.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getWidth() / 4)));

	pickFrame.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() / 4),
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, TCODConsole::root->getHeight() - TCODConsole::root->getHeight() / 4)));

	statistics.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() - TCODConsole::root->getWidth() / 4, 0),
		Point2D(TCODConsole::root->getWidth() - 1, TCODConsole::root->getWidth() / 4)));

	dialog.init(Rectangle(
		Point2D(TCODConsole::root->getWidth() / 2 - 30, 2),
		Point2D(TCODConsole::root->getWidth() / 2 + 30, TCODConsole::root->getHeight() - 2)));

	trade.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	attack.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getWidth() / 4)));

	guiCreature.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getWidth() / 3)));

	guiWeapon.init(Rectangle(
		Point2D(0, 0),
		Point2D(TCODConsole::root->getWidth() / 4, TCODConsole::root->getWidth() / 3)));
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
	if (attack.handleKey(key)) handled = true;
	return handled;
}

void Gui::render(){
	if (inspection.isOpen) inspection.render();
	if (attack.isOpen) attack.render();
	if (log.isOpen) log.render();
	if (statistics.isOpen) statistics.render();
	if (inventory.isOpen) inventory.render();
	if (pickFrame.isOpen) pickFrame.render();
	if (quest.isOpen) quest.render();
	if (help.isOpen) help.render();
	if (dialog.isOpen) dialog.render();
	if (trade.isOpen) trade.render();
	if (guiCreature.isOpen) guiCreature.render();
	if (guiWeapon.isOpen) guiWeapon.render();
}
