#pragma once
#include "ItemContainer.h"

class TradeContainer
{
public:
	int currency;
	ItemContainer items;

	TradeContainer(int currency, ItemContainer items) : 
		currency(currency),
		items(items){};
};