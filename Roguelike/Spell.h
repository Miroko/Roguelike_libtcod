#pragma once
#include <vector>
#include <memory>

class MagicAction;
class Spell
{
public:
	std::string name;
	std::vector<std::shared_ptr<MagicAction>> actions;

	std::string getDescription();

	Spell(std::string name, std::vector<std::shared_ptr<MagicAction>> actions) :
		name(name),
		actions(actions){}
};

