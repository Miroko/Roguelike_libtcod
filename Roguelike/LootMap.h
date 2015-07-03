#pragma once
#include <string>
#include <vector>

class LootMap
{
public:
	std::vector<std::pair<float, std::string>> weapons;
	std::vector<std::pair<float, std::string>> armors;

	LootMap(std::vector<std::pair<float, std::string>> weapons,
		std::vector<std::pair<float, std::string>> armors) :
		weapons(weapons),
		armors(armors){}
};

