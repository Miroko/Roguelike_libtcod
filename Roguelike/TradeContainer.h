#pragma once
#include "ItemContainer.h"

class TradeContainer
{
public:
	static TradeContainer EMPTY;

	int currency;
	int weaponRolls;
	int armorRolls;
	int accessoryRolls;
	int consumableRolls;

	int currentCurrency;
	ItemContainer items;

	void generateItems();

	TradeContainer(int currency, int weaponRolls, int armorRolls, int accessoryRolls, int consumableRolls) :
		currency(currency),
		currentCurrency(currency),
		weaponRolls(weaponRolls),
		armorRolls(armorRolls),
		accessoryRolls(accessoryRolls),
		consumableRolls(consumableRolls){};
};