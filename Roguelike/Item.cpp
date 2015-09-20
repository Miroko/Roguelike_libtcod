#include "Item.h"
#include "Engine.h"
#include "RarityAffixItem.h"

bool Item::operator==(const Item &item){
	if (this == &item) return true;
	else return false;
}

int Item::getValue(){
	int value = (int)(getWeightTotal() * engine::valuePerKg);
	return value;
}

double Item::getWeightBase(){
	return weightKg;
}

double Item::getWeightTotal(){
	double weightTotal = getWeightBase();
	for (auto &affix : rarityAffixes){
		if (affix->isType(affix->ITEM_AFFIX)){
			RarityAffixItem &itemAffix = static_cast<RarityAffixItem&>(*affix);
			weightTotal += getWeightBase() * itemAffix.getWeightModifier();
		}
	}
	return weightTotal;
}

std::string Item::getStatistics(){
	return engine::string.weightKg(getWeightTotal()) + " " + engine::string.currency(getValue());
}

std::string Item::getDescription(){
	std::string description = name;
	RarityAffix* affixPre = getAffixPre();
	if (affixPre != nullptr) description.insert(0, affixPre->name + " ");
	RarityAffix* affixPost = getAffixPost();
	if (affixPost != nullptr) description.append(" of " + affixPost->name);
	return description;
}

void Item::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	//rarity
	int offsetY = 0;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
		TCOD_CENTER,
		rarityType->name);
	//description
	offsetY += 1;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
		TCOD_CENTER,
		getDescription());
	//stats
	offsetY += 2;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getStatistics());
	//affix
	offsetY += 1;
	for (auto &affix : rarityAffixes){
		offsetY += 1;
		frame.printString(
			renderBounds.start.x + 1, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_CENTER,
			affix->getDescription(*this));
	}
}

void Item::renderToFrameLine(GuiFrame &frame, Rectangle &renderBounds, int offsetY){
	//description
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		rarityType->color * Gui::RARITY_COLOR_MULTIPLIER,
		TCOD_LEFT,
		getDescription());
	//stats
	frame.printString(
		renderBounds.start.x + renderBounds.getWidth() / 2, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_LEFT,
		getStatistics());
}