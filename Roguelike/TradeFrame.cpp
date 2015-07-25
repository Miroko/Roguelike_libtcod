#include "TradeFrame.h"
#include "KeyMapping.h"
#include "Direction.h"
#include "Engine.h"
#include "String.h"

bool TradeFrame::handleKey(TCOD_key_t key){
	bool handled = false;
	if (isOpen){
		Point2D direction;		
		direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			errorMessage = ERROR_NONE;
			if (direction == UP){				
				if (selectionCol == 0){
					if (selectionRowPlayer == 0) selectionRowPlayer = currentPlayerItems->items.size() - 1;
					else selectionRowPlayer--;
				}
				else{
					if (selectionRowTrader == 0) selectionRowTrader = currentTraderContainer->items.items.size() - 1;
					else selectionRowTrader--;
				}
				handled = true;
			}
			else if (direction == DOWN){
				if (selectionCol == 0){
					if (selectionRowPlayer == currentPlayerItems->items.size() - 1) selectionRowPlayer = 0;
					else selectionRowPlayer++;
				}
				else{
					if (selectionRowTrader == currentTraderContainer->items.items.size() - 1) selectionRowTrader = 0;
					else selectionRowTrader++;
				}
				handled = true;
			}
			else if (direction == LEFT){
				if (selectionCol == 0) selectionCol = 2;
				else selectionCol--;
				handled = true;
			}
			else if (direction == RIGHT){
				if (selectionCol == 2) selectionCol = 0;
				else selectionCol++;
				handled = true;
			}
			else if (direction == CENTER){
				if (selectionCol == 0){
					auto item = currentPlayerItems->getAt(selectionRowPlayer);
					if (selectedPlayerItems.contains(item)) selectedPlayerItems.remove(item);
					else selectedPlayerItems.add(item);
					calculateCurrencyFromTrade();
					currentPlayerItems->sort();
				}
				else if(selectionCol == 2){
					auto item = currentTraderContainer->items.getAt(selectionRowTrader);
					if (selectedTraderItems.contains(item)) selectedTraderItems.remove(item);
					else selectedTraderItems.add(item);
					calculateCurrencyFromTrade();
					currentTraderContainer->items.sort();
				}
				else{
					makeTrade();
				}
				handled = true;
			}
		}
	}
	if (!handled && isOpen){
		close();
		handled = true;
	}
	return handled;
}

void TradeFrame::render(){
	GuiFrame::render();

	int offsetY = 0;

	//Player
	console->printFrame(0, offsetY, console->getWidth() / 2 - 10, console->getHeight(), true);
	console->printFrame(0, offsetY, console->getWidth() / 2 - 10, 4, true, TCOD_BKGND_DEFAULT, "Player");
	//currency
	printString(0, offsetY, console->getWidth() / 2 - 15, 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_LEFT, TCOD_BKGND_NONE, engine::string.currency(engine::playerHandler.playerInventory.currency));
	//weight
	printString(0, offsetY, console->getWidth() / 2 - 15, 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_RIGHT, TCOD_BKGND_NONE, engine::string.weight(engine::playerHandler.playerInventory.getCurrentWeight()));
	offsetY += 3;
	//items
	int startIndex = selectionRowPlayer;
	if (startIndex > (int)(currentPlayerItems->items.size() - getHeight() + offsetY - 1)){
		startIndex = currentPlayerItems->items.size() - getHeight() + offsetY - 1;
		if (startIndex < 0) startIndex = 0;
	}
	int endIndex = startIndex + getHeight() - offsetY;
	if (endIndex >(int)(currentPlayerItems->items.size() - 1)){
		endIndex = currentPlayerItems->items.size() - 1;
	}
	auto &iterator = currentPlayerItems->items.begin();
	std::advance(iterator, startIndex);
	for (int index = startIndex; index <= endIndex; ++index){
		auto item = *iterator;
		//item
		printString(0, offsetY, console->getWidth() / 2 - 10, 1, item->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, item->rarity.color, TCOD_LEFT, TCOD_BKGND_NONE, item->name);
		//stats
		printString(1, offsetY, console->getWidth() / 2 - 10, 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_CENTER, TCOD_BKGND_NONE, item->getStatistics() + engine::string.currency(item->getValue()) + " " + engine::string.weight(item->weight));
		//operator
		if (index == selectionRowPlayer && selectionCol== 0){
			printString(0, offsetY, console->getWidth() / 2 - 15, 1, Gui::SELECTABLE_OPERATION, Gui::SELECTABLE_OPERATION, TCOD_RIGHT, TCOD_BKGND_NONE, "Select");
			for (int x = 1; x <= console->getWidth() / 2 - 10 - 2; x++){
				console->setCharBackground(x, offsetY + Gui::FRAME_MARGIN + 1, Gui::SELECTABLE_BG);
			}
		}
		else if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(item)){
			printString(0, offsetY, console->getWidth() / 2 - 15, 1, Gui::SELECTABLE_OPERATION, Gui::SELECTABLE_OPERATION, TCOD_RIGHT, TCOD_BKGND_NONE, "Equipped");
		}
		if (selectedPlayerItems.contains(item)){
			for (int x = 1; x <= console->getWidth() / 2 - 10 - 2; x++){
				console->setCharBackground(x, offsetY + Gui::FRAME_MARGIN + 1, Gui::TRADE_SELECTED);
			}
		}
		++offsetY;
		++iterator;
	}

	//Trader
	offsetY = 0;
	console->printFrame(console->getWidth() / 2 + 10, offsetY, console->getWidth() / 2 - 10, console->getHeight(), true);
	console->printFrame(console->getWidth() / 2 + 10, offsetY, console->getWidth() / 2 - 10, 4, true, TCOD_BKGND_SET, "Trader");
	//currency
	printString(console->getWidth() / 2 + 10, offsetY, console->getWidth() / 2 - 15, 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_LEFT, TCOD_BKGND_NONE, engine::string.currency(currentTraderContainer->currency));
	offsetY += 3;
	//items
	startIndex = selectionRowTrader;
	if (startIndex > (int)(currentTraderContainer->items.items.size() - getHeight() + offsetY - 1)){
		startIndex = currentTraderContainer->items.items.size() - getHeight()  + offsetY - 1;
		if (startIndex < 0) startIndex = 0;
	}
	endIndex = startIndex + getHeight() - offsetY;
	if (endIndex >(int)(currentTraderContainer->items.items.size() - 1)){
		endIndex = currentTraderContainer->items.items.size() - 1;
	}
	iterator = currentTraderContainer->items.items.begin();
	std::advance(iterator, startIndex);
	for (int index = startIndex; index <= endIndex; ++index){
		auto item = *iterator;
		//item
		printString(console->getWidth() / 2 + 10, offsetY, console->getWidth() / 2 - 10, 1, item->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, item->rarity.color, TCOD_LEFT, TCOD_BKGND_NONE, item->name);
		//stats
		printString(console->getWidth() / 2 + 10 + 1, offsetY, console->getWidth() / 2 - 10, 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_CENTER, TCOD_BKGND_NONE, item->getStatistics() + engine::string.currency(item->getValue()) + " " + engine::string.weight(item->weight));
		//operator
		if (index == selectionRowTrader && selectionCol == 2){
			printString(console->getWidth() / 2 + 10, offsetY, console->getWidth() / 2 - 15, 1, Gui::SELECTABLE_OPERATION, Gui::SELECTABLE_OPERATION, TCOD_RIGHT, TCOD_BKGND_NONE, "Select");
			for (int x = console->getWidth() / 2 + 10 + 1; x <= console->getWidth() / 2 + 10 + console->getWidth() / 2 - 10 - 2; x++){
				console->setCharBackground(x, offsetY + Gui::FRAME_MARGIN + 1, Gui::SELECTABLE_BG);
			}
		}
		if (selectedTraderItems.contains(item)){
			for (int x = 1; x <= console->getWidth() / 2 - 10 - 2; x++){
				console->setCharBackground(x + console->getWidth() / 2 + 10, offsetY + Gui::FRAME_MARGIN + 1, Gui::TRADE_SELECTED);
			}
		}
		++offsetY;
		++iterator;
	}

	//Currency from trade
	if (currencyFromTrade > 0){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 2, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER, "<-");
	}
	else{
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 2, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER, "->");
	}
	console->printRectEx(console->getWidth() / 2, console->getHeight() / 3, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER, engine::string.currency(currencyFromTrade).c_str());

	//Accept button
	if (selectionCol == 1) console->setDefaultForeground(Gui::SELECTABLE_OPERATION);
	else console->setDefaultForeground(Gui::FRAME_FG);
	console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 4, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER, "ACCEPT");
	blit(console->getWidth() / 3, console->getHeight() / 3 + 4, console->getWidth() / 3, 1, screenBounds.getWidth() / 3, screenBounds.getHeight() / 3 + 4, alphaFg, alphaBg);

	//Error
	if (errorMessage != ERROR_NONE){
		console->setDefaultForeground(Gui::FRAME_FG);
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 12, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
			errorMessage.c_str());
	}
	blit();
}

void TradeFrame::setContainers(ItemContainer &playerItems, TradeContainer &tradeContainer){
	currentPlayerItems = &playerItems;
	currentTraderContainer = &tradeContainer;
}

void TradeFrame::onOpen(){
	errorMessage = ERROR_NONE;
	currencyFromTrade = 0;
	selectionCol = 0;
	selectionRowPlayer = 0;
	selectionRowTrader = 0;
	currentPlayerItems->sort();
	currentTraderContainer->items.sort();
}

void TradeFrame::onClose(){
	selectedPlayerItems.items.clear();
	selectedTraderItems.items.clear();
}

void TradeFrame::calculateCurrencyFromTrade(){
	int currencyFromPlayerItems = 0;
	int currencyFromTraderItems = 0;
	for (auto &item : selectedPlayerItems.items){ currencyFromPlayerItems += item->getValue(); }
	for (auto &item : selectedTraderItems.items){ currencyFromTraderItems += item->getValue(); }
	currencyFromTrade = currencyFromPlayerItems - currencyFromTraderItems;
}

void TradeFrame::makeTrade(){
	if (engine::playerHandler.playerInventory.currency + currencyFromTrade < 0 ||
		currentTraderContainer->currency - currencyFromTrade < 0) errorMessage = ERROR_NOT_ENOUGH_CURRENCY;
	else{
		float newWeight = engine::playerHandler.playerInventory.getCurrentWeight();
		for (auto &item : selectedPlayerItems.items){ newWeight -= item->weight; }
		for (auto &item : selectedTraderItems.items){ newWeight += item->weight; }
		if (newWeight > engine::playerHandler.playerInventory.MAX_WEIGHT) errorMessage = ERROR_TOO_MUCH_WEIGHT;
		else{
			for (auto &item : selectedPlayerItems.items){
				if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(item)){
					engine::playerHandler.playerInventory.unequip(std::static_pointer_cast<Equipment>(item));
				}
				currentPlayerItems->remove(item);
				currentTraderContainer->items.add(item);
			}
			for (auto &item : selectedTraderItems.items){
				currentPlayerItems->add(item);
				currentTraderContainer->items.remove(item);
			}
			engine::playerHandler.playerInventory.currency += currencyFromTrade;
			currentTraderContainer->currency -= currencyFromTrade;

			selectedPlayerItems.items.clear();
			selectedTraderItems.items.clear();
			errorMessage = ERROR_NONE;
			currencyFromTrade = 0;
			selectionCol = 0;
			selectionRowPlayer = 0;
			selectionRowTrader = 0;
		}
	}
}
