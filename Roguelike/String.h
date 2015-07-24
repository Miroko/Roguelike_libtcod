#pragma once
#include <string>

class String
{
public:
	const std::string DIALOG_OPTION_END = "End.";
	const std::string DIALOG_OPTION_TRADE = "Trade.";

	std::string loremIpsum();
	std::string outOf(int current, int max);
	std::string weight(float weight, bool kg = true, int precision = 2);
	std::string currency(int currency);
	std::string multiplier(float multiplier);

	String(){};
};

