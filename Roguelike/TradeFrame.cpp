#include "TradeFrame.h"
#include "KeyMapping.h"
#include "Direction.h"
#include "Engine.h"
#include "String.h"

bool TradeFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	bool handled = false;
	if (isOpen){
		Point2D direction;		
		direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			errorMessage = ERROR_NONE;
			if (direction == UP){				
				if (selectionCol == 0){
					if (selectionRowPlayer == 0) selectionRowPlayer = Engine::GUI.inventory.items.items.size() - 1;
					else selectionRowPlayer--;
				}
				else{
					if (selectionRowTrader == 0) selectionRowTrader = currentTradeContainer->items.size() - 1;
					else selectionRowTrader--;
				}
				handled = true;
			}
			else if (direction == DOWN){
				if (selectionCol == 0){
					if (selectionRowPlayer == Engine::GUI.inventory.items.items.size() - 1) selectionRowPlayer = 0;
					else selectionRowPlayer++;
				}
				else{
					if (selectionRowTrader == currentTradeContainer->items.size() - 1) selectionRowTrader = 0;
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
					auto item = Engine::GUI.inventory.items.items.at(selectionRowPlayer);
					if (playerSelected.contains(*item)) playerSelected.remove(*item);
					else playerSelected.add(item);
					calculateCurrencyFromTrade();
				}
				else if(selectionCol == 2){
					auto item = currentTradeContainer->items.at(selectionRowTrader);
					if (traderSelected.contains(*item)) traderSelected.remove(*item);
					else traderSelected.add(item);
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

void TradeFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	//Frames
	console->printFrame(1, 1, console->getWidth() / 3 - 2, console->getHeight() - 2, true, TCOD_BKGND_DEFAULT, "Player");
	console->printFrame(console->getWidth() + 1 - console->getWidth() / 3, 1, console->getWidth() / 3 - 2, console->getHeight() - 2, true, TCOD_BKGND_DEFAULT, "Trader");

	//Player currency + weight
	console->printFrame(1, 3, console->getWidth() / 3 - 2, 1, true);
	console->printRectEx(2, 2, console->getWidth() / 3 , 1, TCOD_BKGND_NONE, TCOD_LEFT, (std::to_string(Engine::GUI.inventory.currency) + "c").c_str());
	console->printRectEx(console->getWidth() / 3 - 3, 2, console->getWidth() / 3 - 2, 1, TCOD_BKGND_NONE, TCOD_RIGHT,
		(String::weight(Engine::GUI.inventory.getCurrentWeight()) + "/" + String::weight(MAX_WEIGHT) + "kg").c_str());

	//Trader currency
	console->printFrame(console->getWidth() + 1 - console->getWidth() / 3, 3, console->getWidth() / 3 - 2, 1, true);
	console->printRectEx(console->getWidth() + 2 - console->getWidth() / 3, 2, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_LEFT,
		(std::to_string(currentTradeContainer->currency) + "c").c_str());

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
	for (auto &item : Engine::GUI.inventory.items.items){
		if (y == selectionRowPlayer && selectionCol == 0) console->setDefaultForeground(cursorColor);
		else if (playerSelected.contains(*item)) console->setDefaultForeground(selectedColor);
		else console->setDefaultForeground(FG_COLOR);
		console->printRectEx(2, 4 + y, console->getWidth()/3, 1, TCOD_BKGND_NONE, TCOD_LEFT,
			item->getDescription().c_str());
		blit(2, 4 + y, console->getWidth()/3, 1, bounds.start.x + 2, bounds.start.y + 4 + y, alphaFg, alphaBg);
		++y;
	}

	//Accept button
	if (selectionCol == 1) console->setDefaultForeground(cursorColor);
	else console->setDefaultForeground(FG_COLOR);
	console->printRectEx(console->getWidth() / 2, console->getHeight() / 3 + 4, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_CENTER,
		"ACCEPT");
	blit(console->getWidth() / 3, console->getHeight() / 3 + 4, console->getWidth() / 3, 1, bounds.getWidth() / 3, bounds.getHeight() / 3 + 4, alphaFg, alphaBg);

	//Trader items
	y = 0;
	for (auto &item : currentTradeContainer->items){
		if (y == selectionRowTrader && selectionCol == 2) console->setDefaultForeground(cursorColor);
		else if (traderSelected.contains(*item)) console->setDefaultForeground(selectedColor);
		else console->setDefaultForeground(FG_COLOR);
		console->printRectEx(console->getWidth() + 2 - console->getWidth() / 3, 4 + y, console->getWidth() / 3, 1, TCOD_BKGND_NONE, TCOD_LEFT,
			item->getDescription().c_str());
		blit(console->getWidth() + 2 - console->getWidth() / 3, 4 + y, console->getWidth() / 3 - 2, 1, bounds.end.x + 2 - console->getWidth() / 3, bounds.start.y + 4 + y, alphaFg, alphaBg);
		++y;
	}


}

void TradeFrame::setTradeContainer(std::shared_ptr<TradeContainer> &tradeContainer){
	currentTradeContainer = tradeContainer;
}

void TradeFrame::onOpen(){
	errorMessage = ERROR_NONE;
	currencyFromTrade = 0;
	selectionCol = 0;
	selectionRowPlayer = 0;
	selectionRowTrader = 0;
}

void TradeFrame::onClose(){
	playerSelected.items.clear();
	traderSelected.items.clear();
}

void TradeFrame::calculateCurrencyFromTrade(){
	int currencyFromPlayerItems = 0;
	int currencyFromTraderItems = 0;
	for (auto &item : playerSelected.items){ currencyFromPlayerItems += item->getValue(); }
	for (auto &item : traderSelected.items){ currencyFromTraderItems += item->getValue(); }
	currencyFromTrade = currencyFromPlayerItems - currencyFromTraderItems;
}

void TradeFrame::makeTrade(){
	if (Engine::GUI.inventory.currency + currencyFromTrade < 0 ||
		currentTradeContainer->currency - currencyFromTrade < 0) errorMessage = ERROR_NOT_ENOUGH_CURRENCY;
	else{
		float newWeight = Engine::GUI.inventory.getCurrentWeight();
		for (auto &item : playerSelected.items){ newWeight -= item->weight; }
		for (auto &item : traderSelected.items){ newWeight += item->weight; }
		if (newWeight > MAX_WEIGHT) errorMessage = ERROR_TOO_MUCH_WEIGHT;
		else{
			for (auto &item : playerSelected.items){
				Engine::GUI.inventory.items.remove(*item);
				currentTradeContainer->add(item);
			}
			for (auto &item : traderSelected.items){
				currentTradeContainer->remove(*item);
				Engine::GUI.inventory.items.add(item);
			}
			Engine::GUI.inventory.currency += currencyFromTrade;
			currentTradeContainer->currency -= currencyFromTrade;

			playerSelected.items.clear();
			traderSelected.items.clear();
			currencyFromTrade = 0;
		}
	}
}
