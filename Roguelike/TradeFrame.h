#pragma once
#include "GuiFrame.h"
#include "TradeContainer.h"

class TradeFrame : public GuiFrame
{
private:
	const std::string ERROR_NOT_ENOUGH_CURRENCY = "Not enough currency";
	const std::string ERROR_TOO_MUCH_WEIGHT = "Can't carry that much";
	const std::string ERROR_NONE = "";

	TCODColor cursorColor = TCODColor::lighterGreen;
	TCODColor selectedColor = TCODColor::yellow;
	std::shared_ptr<TradeContainer> currentTradeContainer;
	int selectionCol; // 0player 1accept 2trader
	int selectionRowPlayer;
	int selectionRowTrader;
	PointerContainer<Item> playerSelected;
	PointerContainer<Item> traderSelected;
	int currencyFromTrade;
	void calculateCurrencyFromTrade();
	std::string errorMessage = "";
	void makeTrade();
public:
	void setTradeContainer(std::shared_ptr<TradeContainer> &tradeContainer);

	bool handleKey(TCOD_key_t key, bool &requireUpdate);
	void GuiFrame::render();
	void onOpen();
	void onClose();

	TradeFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Trade"){};
};
