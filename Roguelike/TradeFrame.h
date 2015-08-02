#pragma once
#include "GuiFrame.h"
#include "GuiBox.h"
#include "GuiGameObjectDisplay.h"
#include "GuiSelectableItemList.h"
#include "TradeContainer.h"

class TradeFrame : public GuiFrame
{
private:
	const std::string ERROR_NOT_ENOUGH_CURRENCY = "Not enough currency";
	const std::string ERROR_TOO_MUCH_WEIGHT = "Can't carry that much";
	const std::string ERROR_NONE = "";

	//Player
	Rectangle guiPlayerTopBoxBounds;
	GuiBox guiPlayerTopBox;

	Rectangle guiPlayerDisplayBoxBounds;
	GuiBox guiPlayerDisplayBox;
	Rectangle guiPlayerItemDisplayBounds;
	GuiGameObjectDisplay guiPlayerItemDisplay;

	Rectangle guiPlayerSelectableListBoxBounds;
	GuiBox guiPlayerSelectableListBox;
	Rectangle guiPlayerSelectableItemListBounds;
	GuiSelectableItemList guiPlayerSelectableItemList;

	ItemContainer selectedPlayerItems;

	//Trader
	Rectangle guiTraderTopBoxBounds;
	GuiBox guiTraderTopBox;

	Rectangle guiTraderDisplayBoxBounds;
	GuiBox guiTraderDisplayBox;
	Rectangle guiTraderItemDisplayBounds;
	GuiGameObjectDisplay guiTraderItemDisplay;

	Rectangle guiTraderSelectableListBoxBounds;
	GuiBox guiTraderSelectableListBox;
	Rectangle guiTraderSelectableItemListBounds;
	GuiSelectableItemList guiTraderSelectableItemList;

	TradeContainer *currentTraderContainer;
	ItemContainer selectedTraderItems;

	int selectionCol; // 0player 1accept 2trader
	int selectionRowPlayer;
	int selectionRowTrader;
	int currencyFromTrade;
	std::string errorMessage = "";

	void calculateCurrencyFromTrade();
	void makeTrade();

public:
	void setContainers(ItemContainer &playerItems, TradeContainer &traderContainer);
	bool handleKey(TCOD_key_t key);
	void GuiFrame::render();
	void onOpen();
	void onClose();
	void init(Rectangle bounds);

	TradeFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Trade"),
		guiPlayerTopBox("Player"),
		guiTraderTopBox("Trader"){};
};
