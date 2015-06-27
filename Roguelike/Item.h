#pragma once
#include "GameObject.h"
#include <memory>
#include <string>

class RarityType;
class RarityEffect;
class Item : public GameObject
{
private:
	const int VALUE_WEIGHT_MULTIPLIER = 1.2;

public:
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
	Point2D location;
	RarityType *rarity = nullptr;
	RarityEffect *rarityEffect = nullptr;
	float weight; 	// Kg

	virtual int getValue();

	virtual std::string getStatistics();
	virtual std::string getDescription();


	void print(int x, int y, int width, int height, TCODConsole &console);
	void printWithBg(int x, int y, int width, int height, TCODConsole &console);

	bool operator==(const Item &item);

	Item(std::string name, Glyph glyph, float weight, Type type)
		: GameObject(name, glyph), weight(weight), type(type){};
};

