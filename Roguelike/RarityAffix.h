#pragma once
#include <string>

class RarityAffix
{
public:
	enum Type{
		ITEM_AFFIX,
		EQUIPMENT_AFFIX,
		ARMOR_AFFIX,
		WEAPON_AFFIX,
		ACCESSORY_AFFIX,
		CONSUMABLE_AFFIX,
		CREATURE_AFFIX
	};

	Type type;
	std::string name;
	bool isType(Type type);
	virtual std::string getDescription() = 0;

	RarityAffix(std::string name, Type type) :
		name(name),
		type(type){}
};

