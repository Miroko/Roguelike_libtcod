#pragma once
#include "GameObject.h"
#include <memory>
class Item : public GameObject
{
public:

	template <typename T> static std::shared_ptr<T> newItem(const T &itemTemplate){
		return std::shared_ptr<T>(new T(itemTemplate));
	}

	Point2D location;

	enum Type{
		WEAPON,
		CONSUMABLE
	};
	Type type;

	// Kg
	float weight;

	bool operator==(const Item &item);

	Item(Glyph glyph, std::string name, float weight, Type type)
		: GameObject(glyph, name), weight(weight), type(type){};
};

