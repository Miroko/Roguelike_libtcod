#pragma once
#include "CreatureLimb.h"
#include <vector>
#include <string>

class TemplateCreature
{
public:
	std::string id;
	std::string name;
	std::vector<CreatureLimb> limbs;

	TemplateCreature(std::string id, std::string name, std::vector<CreatureLimb> limbs) :
		id(id), name(name), limbs(limbs){}
};

