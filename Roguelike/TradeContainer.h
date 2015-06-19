#pragma once
#include "PointerContainer.h"
class TradeContainer : public PointerContainer<Item>
{
public:
	int currency;

	TradeContainer(int currency, std::vector<std::shared_ptr<Item>> items) : PointerContainer(items), currency(currency){};
};