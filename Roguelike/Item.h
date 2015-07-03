#pragma once
#include "GameObject.h"
#include "RarityType.h"
#include <memory>
#include <string>

class Item : public GameObject
{
private:
	const float VALUE_WEIGHT_MULTIPLIER = 1.2f;

public:
	RarityType &rarity;

	Point2D location;
	float weight; 	// Kg

	bool isWeapon();
	bool isArmor();

	virtual int getValue();

	virtual std::string getStatistics();
	virtual std::string getDescription();

	void print(int x, int y, int width, int height, TCODConsole &console);
	void printWithBg(int x, int y, int width, int height, TCODConsole &console);

	bool operator==(const Item &item);

	Item(std::string name, Glyph glyph, float weight, Type type, RarityType &rarity)
		: GameObject(name, type, glyph),
		weight(weight),
		rarity(rarity){};
};

