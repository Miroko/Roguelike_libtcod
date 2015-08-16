#pragma once
#include <string>

class RarityAffix
{
public:
	std::string name;
	virtual std::string getDescription() = 0;

	RarityAffix(std::string name) :
		name(name){}
};

