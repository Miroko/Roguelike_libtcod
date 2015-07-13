#pragma once
#include "GuiFrame.h"
#include "TradeContainer.h"

class TradeFrame : public GuiFrame
{
private:
	const std::string ERROR_NOT_ENOUGH_CURRENCY = "Not enough currency";
	const std::string ERROR_TOO_MUCH_WEIGHT = "Can't carry that much";
	const std::string ERROR_NONE = "";

	ItemContainer *currentPlayerItems;
	TradeContainer *currentTraderContainer;

	ItemContainer selectedPlayerItems;
	ItemContainer selectedTraderItems;

	int selectionCol; // 0player 1accept 2trader
	int selectionRowPlayer;
	int selectionRowTrader;
	int currencyFromTrade;
	std::string errorMessage = "";

	void calculateCurrencyFromTrade();
	void makeTrade();

public:
	void setContainers(ItemContainer &playerItems, TradeContainer &tradeContainer);

	bool handleKey(TCOD_key_t key);
	void GuiFrame::render();
	void onOpen();
	void onClose();

	TradeFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Trade"){};
};
