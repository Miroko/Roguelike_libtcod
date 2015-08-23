#pragma once
#include <string>

class CreatureAction
{
public:
	std::string name;
	std::string logDescription;

	CreatureAction(std::string name, std::string logDescription) :
		name(name),
		logDescription(logDescription){}
	CreatureAction(){}
};

