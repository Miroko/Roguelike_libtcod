#pragma once
#include "GameObject.h"
#include <memory>
#include <string>

const int VALUE_PER_KG = 1;

class Item : public GameObject
{
public:

	template <typename T> static std::shared_ptr<T> newItem(const std::shared_ptr<T> &itemTemplate){
		return std::shared_ptr<T>(new T(*itemTemplate));
	}

	Point2D location;

	enum Type{
		WEAPON_MELEE,
		WEAPON_RANGED,
		ARMOR_HEAD,
		ARMOR_BODY,
		ARMOR_HAND,
		ARMOR_LEG,
		CONSUMABLE
	};
	Type type;

	// Kg
	float weight;

	virtual std::string getDescription();
	virtual int getValue();

	bool operator==(const Item &item);

	Item(Glyph glyph, std::string name, float weight, Type type)
		: GameObject(glyph, name, true), weight(weight), type(type){};
};

