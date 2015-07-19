#pragma once
#include "ItemContainer.h"

class TradeContainer
{
public:
	static TradeContainer EMPTY;

	int currency;
	int weaponRolls;
	int armorRolls;
	int potionRolls;

	int currentCurrency;
	ItemContainer items;

	void generateItems();

	TradeContainer(int currency, int weaponRolls, int armorRolls, int potionRolls) :
		currency(currency), weaponRolls(weaponRolls), armorRolls(armorRolls), potionRolls(potionRolls){};
};