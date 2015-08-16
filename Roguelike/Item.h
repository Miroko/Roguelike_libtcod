#pragma once
#include "GameObject.h"
#include "RarityMod.h"
#include <memory>
#include <string>

class Item : public GameObject, public RarityMod
{
private:
	double weightKg;

public:
	Point2D location;
	int limbsRequiredToHold;

	virtual int getValue();
	double getWeight();

	virtual std::string getStatistics();
	virtual std::string getDescription();

	bool operator==(const Item &item);

	Item(RarityMod rarityMod, GameObject gameObject, double weightKg, int limbsRequiredToHold = 1) :
		RarityMod(rarityMod),
		GameObject(gameObject),
		weightKg(weightKg),
		limbsRequiredToHold(limbsRequiredToHold){};
};

