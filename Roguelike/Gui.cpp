#include "Gui.h"

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

void Gui::render(float elapsed){
	if (inspection.isOpen) inspection.render(elapsed);
	if (attack.isOpen) attack.render(elapsed);
	if (log.isOpen) log.render(elapsed);
	if (statistics.isOpen) statistics.render(elapsed);
	if (inventory.isOpen) inventory.render(elapsed);
	if (equipment.isOpen) equipment.render(elapsed);
	if (pickFrame.isOpen) pickFrame.render(elapsed);
	if (quest.isOpen) quest.render(elapsed);
	if (help.isOpen) help.render(elapsed);
	if (dialog.isOpen) dialog.render(elapsed);
	if (trade.isOpen) trade.render(elapsed);
}
