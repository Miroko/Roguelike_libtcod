#pragma once
#include "CreatureLimb.h"
#include <vector>
#include <string>

class TemplateCreatureBase
{
public:
	std::vector<CreatureLimb> limbs;

	TemplateCreatureBase(std::vector<CreatureLimb> limbs) :
		limbs(limbs){}
	TemplateCreatureBase(){}
};

