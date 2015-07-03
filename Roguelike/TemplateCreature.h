#pragma once
#include "CreatureLimb.h"
#include "Glyph.h"
#include <vector>
#include <string>

class TemplateCreature
{
public:
	std::string id;
	std::string name;
	Glyph glyph;
	std::vector<CreatureLimb> limbs;

	TemplateCreature(std::string id, std::string name, Glyph glyph, std::vector<CreatureLimb> limbs) :
		id(id), name(name), glyph(glyph), limbs(limbs){}
};

