#pragma once
#include <string>

class String
{
public:
	const std::string DIALOG_OPTION_END = "End.";
	const std::string DIALOG_OPTION_TRADE = "Trade.";

	std::string loremIpsum();
	std::string outOf(int current, int max);
	std::string weightKg(double weightKg, bool kg = true, int precision = 2);
	std::string currency(int currency);
	std::string multiplier(double multiplier);
	std::string damage(int damage);
	std::string range(int range);
	std::string defence(int defence);
	std::string duration(int duration);
	std::string durability(int current, int max);
	std::string percentage(double percentage);

	String(){};
};

