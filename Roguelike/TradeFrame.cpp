#include "TradeFrame.h"
#include "KeyMapping.h"
#include "Direction.h"
#include "Engine.h"
#include "String.h"

bool TradeFrame::handleKey(TCOD_key_t key){
	bool handled = false;
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			//clear error message
			errorMessage = ERROR_NONE;
			//change item
			if (direction == UP || direction == DOWN ){
				if (selectionCol == 0){
					handled = guiPlayerSelectableItemList.handleKey(key);
				}
				else if(selectionCol == 2){
					handled = guiTraderSelectableItemList.handleKey(key);
				}
			}
			//select item for trade or accept trade
			else if (direction == CENTER){
				if (selectionCol == 0){
					handled = guiPlayerSelectableItemList.handleKey(key);
				}
				else if (selectionCol == 1){
					makeTrade();
					handled = true;
				}
				else if (selectionCol == 2){
					handled = guiTraderSelectableItemList.handleKey(key);
				}
			}
			//change column
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
		}
		if (!handled){
			close();
			handled = true;
		}
	}
	return handled;
}

void TradeFrame::render(){
	GuiFrame::render();
	//Player
	guiPlayerTopBox.renderTo(*this, guiPlayerTopBoxBounds);
	//currency
	printString(
		guiPlayerTopBoxBounds.start.x, guiPlayerTopBoxBounds.start.y,
		guiPlayerTopBoxBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		engine::string.currency(engine::playerHandler.getPlayerCreature()->inventory.currency));
	//weightKg
	printString(
		guiPlayerTopBoxBounds.start.x, guiPlayerTopBoxBounds.start.y,
		guiPlayerTopBoxBounds.getWidth() - 6, 0,
		Gui::FRAME_FG,
		TCOD_RIGHT,
		engine::string.weightKg(engine::playerHandler.getPlayerCreature()->inventory.getTotalWeight()));
	guiPlayerDisplayBox.renderTo(*this, guiPlayerDisplayBoxBounds);
	guiPlayerItemDisplay.renderTo(*this, guiPlayerItemDisplayBounds);
	guiPlayerSelectableListBox.renderTo(*this, guiPlayerSelectableListBoxBounds);
	guiPlayerSelectableItemList.renderTo(*this, guiPlayerSelectableItemListBounds);

	//currency for trade
	printString(
		0, getHeight() / 2,
		getWidth(), getHeight(),
		Gui::FRAME_FG,
		TCOD_CENTER,
		engine::string.currency(currencyFromTrade).c_str());
	//arrow
	std::string arrowDirection;
	if (currencyFromTrade > 0) arrowDirection = "<-";
	else arrowDirection = "->";
	printString(
		0, getHeight() / 2 + 2,
		getWidth(), getHeight(),
		Gui::FRAME_FG,
		TCOD_CENTER,
		arrowDirection);
	//accept button
	TCODColor acceptColor;
	if (selectionCol == 1) acceptColor = Gui::SELECTABLE_OPERATION;
	else acceptColor = Gui::FRAME_FG;
	printString(
		0, getHeight() / 2 + 4,
		getWidth(), getHeight(),
		acceptColor,
		TCOD_CENTER,
		"Accept");
	//error
	if (errorMessage != ERROR_NONE){
		printString(
			0, getHeight() / 2 + 6,
			getWidth(), getHeight(),
			Gui::FRAME_FG,
			TCOD_CENTER,
			errorMessage.c_str());
	}

	//Trader
	guiTraderTopBox.renderTo(*this, guiTraderTopBoxBounds);
	//currency
	printString(
		guiTraderTopBoxBounds.start.x, guiTraderTopBoxBounds.start.y,
		guiTraderTopBoxBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		engine::string.currency(currentTraderContainer->currentCurrency));
	guiTraderDisplayBox.renderTo(*this, guiTraderDisplayBoxBounds);
	guiTraderItemDisplay.renderTo(*this, guiTraderItemDisplayBounds);
	guiTraderSelectableListBox.renderTo(*this, guiTraderSelectableListBoxBounds);
	guiTraderSelectableItemList.renderTo(*this, guiTraderSelectableItemListBounds);
	blit();
}

void TradeFrame::setContainers(ItemContainer &playerItems, TradeContainer &traderContainer){
	guiPlayerSelectableItemList.setItemContainer(playerItems);

	currentTraderContainer = &traderContainer;
	guiTraderSelectableItemList.setItemContainer(currentTraderContainer->items);
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
	for (auto &item : selectedPlayerItems.items){ currencyFromPlayerItems += item->getValue(); }
	for (auto &item : selectedTraderItems.items){ currencyFromTraderItems += item->getValue(); }
	currencyFromTrade = currencyFromPlayerItems - currencyFromTraderItems;
}

void TradeFrame::makeTrade(){
	if (engine::playerHandler.getPlayerCreature()->inventory.currency + currencyFromTrade < 0 ||
		currentTraderContainer->currency - currencyFromTrade < 0) errorMessage = ERROR_NOT_ENOUGH_CURRENCY;
	else{
		double newWeight = engine::playerHandler.getPlayerCreature()->inventory.getTotalWeight();
		for (auto &item : selectedPlayerItems.items){ newWeight -= item->getWeight(); }
		for (auto &item : selectedTraderItems.items){ newWeight += item->getWeight(); }
		if (newWeight > engine::weightCarryMax) errorMessage = ERROR_TOO_MUCH_WEIGHT;
		else{
			for (auto &item : selectedPlayerItems.items){
				if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(*item)){
					engine::playerHandler.getPlayerCreature()->inventory.unequip(item);
				}
				guiPlayerSelectableItemList.itemContainer->remove(item);
				currentTraderContainer->items.add(item);
			}
			for (auto &item : selectedTraderItems.items){
				guiPlayerSelectableItemList.itemContainer->add(item);
				currentTraderContainer->items.remove(item);
			}
			engine::playerHandler.getPlayerCreature()->inventory.currency += currencyFromTrade;
			currentTraderContainer->currentCurrency -= currencyFromTrade;

			selectedPlayerItems.items.clear();
			selectedTraderItems.items.clear();
			errorMessage = ERROR_NONE;
			currencyFromTrade = 0;
			selectionCol = 0;
			selectionRowPlayer = 0;
			selectionRowTrader = 0;

			guiPlayerSelectableItemList.itemContainer->sort();
			guiPlayerSelectableItemList.updateSelection();

			guiTraderSelectableItemList.itemContainer->sort();
			guiTraderSelectableItemList.updateSelection();
		}
	}
}

void TradeFrame::init(Rectangle bounds){
	GuiFrame::init(bounds);
	//Player
	guiPlayerTopBoxBounds = Rectangle(Point2D(0, 0), Point2D(bounds.getWidth()/2 - 10, 3));
	guiPlayerDisplayBoxBounds = Rectangle(Point2D(0, 3), Point2D(bounds.getWidth() / 2 - 10, 14));
	guiPlayerItemDisplayBounds = Rectangle(Point2D(0, 3), Point2D(bounds.getWidth() / 2 - 14, 14));
	guiPlayerSelectableListBoxBounds = Rectangle(Point2D(0, 14), Point2D(bounds.getWidth() / 2 - 10, bounds.getHeight() - 1));
	guiPlayerSelectableItemListBounds = Rectangle(Point2D(0, 14), Point2D(getWidth() / 2 - 13, getHeight()));
	guiPlayerSelectableItemList.setGetOperationsFunction(
		[this](std::shared_ptr<Item> item, bool selected) -> std::vector<std::string>{
		if (selected){
			//update item in display
			guiPlayerItemDisplay.setDisplayedObject(item.get());
			if(!selectedPlayerItems.contains(item)){
				return{ "Add" };
			}
			else{
				return{ "Remove" };
			}
		}
		else if (selectedPlayerItems.contains(item)){
			return{ "In trade" };
		}
		else if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(*item)){
			return{ "Equipped" };
		}
		else return{ "" };
	});
	guiPlayerSelectableItemList.setOnOperationSelectedFunction(
		[this](std::shared_ptr<Item> item, std::string operation){
		if (selectedPlayerItems.contains(item)) selectedPlayerItems.remove(item);
		else selectedPlayerItems.add(item);
		calculateCurrencyFromTrade();
	});
	//Trader
	guiTraderTopBoxBounds = Rectangle(Point2D(bounds.getWidth() / 2 + 9, 0), Point2D(bounds.getWidth(), 3));
	guiTraderDisplayBoxBounds = Rectangle(Point2D(bounds.getWidth() / 2 + 9, 3), Point2D(bounds.getWidth(), 14));
	guiTraderItemDisplayBounds = Rectangle(Point2D(bounds.getWidth() / 2 + 4, 3), Point2D(bounds.getWidth(), 14));
	guiTraderSelectableListBoxBounds = Rectangle(Point2D(bounds.getWidth() / 2 + 9, 14), Point2D(bounds.getWidth(), bounds.getHeight() - 1));
	guiTraderSelectableItemListBounds = Rectangle(Point2D(bounds.getWidth() / 2 + 9, 14), Point2D(getWidth(), getHeight()));
	guiTraderSelectableItemList.setGetOperationsFunction(
		[this](std::shared_ptr<Item> item, bool selected) -> std::vector<std::string>{
		if (selected){
			//update item in display
			guiTraderItemDisplay.setDisplayedObject(item.get());
			if (!selectedTraderItems.contains(item)){
				return{ "Add" };
			}
			else{
				return{ "Remove" };
			}
		}
		else if (selectedTraderItems.contains(item)){
			return{ "In trade" };
		}
		else return{ "" };
	});
	guiTraderSelectableItemList.setOnOperationSelectedFunction(
		[this](std::shared_ptr<Item> item, std::string operation){
		if (selectedTraderItems.contains(item)) selectedTraderItems.remove(item);
		else selectedTraderItems.add(item);
		calculateCurrencyFromTrade();
	});
}