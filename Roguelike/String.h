#pragma once
#include <string>

class String
{
public:
	const std::string DIALOG_OPTION_END = "End.";
	const std::string DIALOG_OPTION_TRADE = "Trade.";

	std::string loremIpsum();
	std::string outOf(int current, int max);
	std::string multiplier(double multiplier);
	std::string percentageValue(double percentageValue);
	std::string value(int value);

	std::string weightKg(double weightKg, bool kg = true, int precision = 2, bool showPos = false);
	std::string currency(int currency);
	std::string damage(int damage);
	std::string range(int range);
	std::string defence(int defence);
	std::string potency(double potency);
	std::string concentration(double concentration);
	std::string duration(int duration);
	std::string magic(int magic);
	std::string spellPower(double spellPower);
	std::string durability(int current, int max);

	String(){};
};

