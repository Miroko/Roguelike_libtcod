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
				}
				else if(selectionCol == 2){
					auto item = currentTraderContainer->items.getAt(selectionRowTrader);
					if (selectedTraderItems.contains(item)) selectedTraderItems.remove(item);
					else selectedTraderItems.add(item);
					calculateCurrencyFromTrade();
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

	//Frames
	console->printFrame(1, 1, console->getWidth() / 3 - 2, console->getHeight() - 2, true, TCOD_BKGND_DEFAULT, "Player");
	console->printFrame(console->getWidth() + 1 - console->getWidth() / 3, 1, console->getWidth() / 3 - 2, console->getHeight() - 2, true, TCOD_BKGND_DEFAULT, "Trader");

	//Player currency + weight
	console->printFrame(1, 3, console->getWidth() / 3 - 2, 1, true);
	console->printRectEx(2, 2, console->getWidth() / 3 , 1, TCOD_BKGND_NONE, TCOD_LEFT, engine::string.currency(engine::playerHandler.playerInventory.currency).c_str());
	console->printRectEx(console->getWidth() / 3 - 3, 2, console->getWidth() / 3 - 2, 1, TCOD_BKGND_NONE, TCOD_RIGHT,
		(engine::string.weight(engine::playerHandler.playerInventory.getCurrentWeight(), false) + "/" + engine::string.weight(engine::playerHandler.playerInventory.getCurrentWeight())).c_str());

	//Trader currency
	console->printFrame(console->getWidth() + 1 - console->getWidth() / 3, 3, console->getWidth() / 3 - 2, 1, true);
	console->printRectEx(console->getWidth() + 2 - console->getWidth() / 3, 2, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_LEFT,
		(std::to_string(currentTraderContainer->currency) + "c").c_str());

	//Currency from trade
	if (currencyFromTrade > 0){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 2, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
			"<-");
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
			(std::to_string(currencyFromTrade) + "c").c_str());
	}
	else{
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 2, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
			"->");
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
			(std::to_string(abs(currencyFromTrade)) + "c").c_str());
	}
	//Error
	if (errorMessage != ERROR_NONE){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 12, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
			errorMessage.c_str());
	}
	blit();

	//Player items
	int y = 0;
	for (auto &item : currentPlayerItems->items){
		if (y == selectionRowPlayer && selectionCol == 0){
			//cursor
			console->setDefaultForeground(cursorColor);
			item->print(2, 4 + y, console->getWidth() / 3, 1, *console);
		}
		else if (currentPlayerItems->contains(item)){
			//selected for trade
			console->setDefaultForeground(selectedColor);
			item->print(2, 4 + y, console->getWidth() / 3, 1, *console);
		}
		else{
			//normal
			console->setDefaultForeground(FG_COLOR);
			item->print(2, 4 + y, console->getWidth() / 3, 1, *console);
		}
		blit(2, 4 + y, console->getWidth()/3, 1, screenBounds.start.x + 2, screenBounds.start.y + 4 + y, alphaFg, alphaBg);
		++y;
	}

	//Accept button
	if (selectionCol == 1) console->setDefaultForeground(cursorColor);
	else console->setDefaultForeground(FG_COLOR);
	console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 4, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
		"ACCEPT");
	blit(console->getWidth() / 3, console->getHeight() / 3 + 4, console->getWidth() / 3, 1, screenBounds.getWidth() / 3, screenBounds.getHeight() / 3 + 4, alphaFg, alphaBg);

	//Trader items
	y = 0;
	for (auto &item : currentTraderContainer->items.items){
		if (y == selectionRowTrader && selectionCol == 2){
			//cursor
			console->setDefaultForeground(cursorColor);
			item->printWithBg(console->getWidth() + 2 - console->getWidth() / 3, 4 + y, console->getWidth() / 3, 1, *console);
		}
		else if (currentTraderContainer->items.contains(item)){
			//selected for trade
			console->setDefaultForeground(selectedColor);
			item->print(console->getWidth() + 2 - console->getWidth() / 3, 4 + y, console->getWidth() / 3, 1, *console);
		}
		else{
			//normal
			console->setDefaultForeground(FG_COLOR);
			item->print(2 + console->getWidth() - console->getWidth() / 3, 4 + y, console->getWidth() / 3, 1, *console);
		}
		blit(2 + console->getWidth() - console->getWidth() / 3, 4 + y, console->getWidth() / 3 - 2, 1, screenBounds.end.x + 2 - console->getWidth() / 3, screenBounds.start.y + 4 + y, alphaFg, alphaBg);
		++y;
	}
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
}

void TradeFrame::onClose(){
	selectedPlayerItems.items.clear();
	selectedTraderItems.items.clear();
}

void TradeFrame::calculateCurrencyFromTrade(){
	int currencyFromPlayerItems = 0;
	int currencyFromTraderItems = 0;
	for (auto &item : currentPlayerItems->items){ currencyFromPlayerItems += item->getValue(); }
	for (auto &item : currentTraderContainer->items.items){ currencyFromTraderItems += item->getValue(); }
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
			currencyFromTrade = 0;
		}
	}
}
