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
	double getWeightBase();
	double getWeightTotal();

	std::string GuiObject::getStatistics() override;
	std::string GuiObject::getDescription() override;
	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;
	void GuiObject::renderToFrameLine(GuiFrame &frame, Rectangle &renderBounds, int offsetY) override;

	bool operator==(const Item &item);

	Item(RarityMod rarityMod, GameObject gameObject, double weightKg, int limbsRequiredToHold = 1) :
		RarityMod(rarityMod),
		GameObject(gameObject),
		weightKg(weightKg),
		limbsRequiredToHold(limbsRequiredToHold){};
};

