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
	int limbsRequiredToHold;

	virtual int getValue();
	virtual std::string getStatistics();
	virtual std::string getDescription();

	bool operator==(const Item &item);

	Item(std::string name, Glyph glyph, float weight, Type type, RarityType &rarity, int limbsRequiredToHold = 1) :
		GameObject(name, type, glyph),
		weight(weight),
		rarity(rarity),
		limbsRequiredToHold(limbsRequiredToHold){};
};

