#include "QuestTheGoblinKing.h"
#include "Forest.h"
#include "Engine.h"
#include "Weapon.h"

//Forest
void QuestTheGoblinKing::PhaseWayThroughForest::ForestGoblin::onGatePlace(Point2D &location){

}

void QuestTheGoblinKing::PhaseWayThroughForest::ForestGoblin::onStonePlaced(Point2D &location){

}

//Village phase
std::string QuestTheGoblinKing::PhaseVillage::DialogBlacksmith::getText(){
	return speaker->name + " greets me.\n\n" + Dialog::getText();
}
std::string QuestTheGoblinKing::PhaseVillage::DialogAlchemist::getText(){
	return speaker->name + " mumbles something to himself...\n\n" + Dialog::getText();
}
std::shared_ptr<Area> QuestTheGoblinKing::PhaseVillage::generateArea(){
	std::shared_ptr<VillageMain> area = std::shared_ptr<VillageMain>(new VillageMain());
	area->generate();

	blacksmithTradeContainer.items.removeAll();
	blacksmithTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createWeapon("weapon_sword", *engine::objectLibrary.getRarity("rarity_uncommon"))));
	blacksmithTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createWeapon("weapon_sword", *engine::objectLibrary.getRarity("rarity_uncommon"))));
	blacksmithTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createWeapon("weapon_sword", *engine::objectLibrary.getRarity("rarity_common"))));

	alchemistTradeContainer.items.removeAll();
	alchemistTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createPotion("potion_health")));
	alchemistTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createPotion("potion_health")));
	alchemistTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createPotion("potion_health")));
	alchemistTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createPotion("potion_health")));
	alchemistTradeContainer.items.add(std::static_pointer_cast<Item>(engine::objectFactory.createPotion("potion_health")));

	return area;
}
std::shared_ptr<Dialog> const &QuestTheGoblinKing::PhaseVillage::getDialog(Creature &speaker){
	if (speaker.presetId == "human_blacksmith"){
		dialogBlacksmith->setSpeaker(speaker);
		return dialogBlacksmith;
	}
	else if (speaker.presetId == "human_alchemist"){
		dialogAlchemist->setSpeaker(speaker);
		return dialogAlchemist;
	}
	else return QuestPhase::getDialog(speaker);
}
TradeContainer &QuestTheGoblinKing::PhaseVillage::getTradeContainer(Creature &trader){
	if (trader.presetId == "human_blacksmith"){
		return blacksmithTradeContainer;
	} 
	else if (trader.presetId == "human_alchemist"){
		return alchemistTradeContainer;
	}
	else return QuestPhase::getTradeContainer(trader);
}

//Forest phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseWayThroughForest::generateArea(){
	std::shared_ptr<ForestGoblin> area = std::shared_ptr<ForestGoblin>(new ForestGoblin());
	area->generate();
	int drops = area->getBounds().getSize() / 500;
	for (int drop = drops; drop > 0; --drop){
		Point2D location = engine::random.point(area->getBounds());
		area->dropGoblin.drop(location, 2, *area);
	}
	return area;
}
std::shared_ptr<Dialog> const &QuestTheGoblinKing::PhaseWayThroughForest::getDialog(Creature &owner){
	return QuestPhase::getDialog(owner);
}
TradeContainer &QuestTheGoblinKing::PhaseWayThroughForest::getTradeContainer(Creature &owner){
	return QuestPhase::getTradeContainer(owner);
}

//Cave phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseInCave::generateArea(){
	std::shared_ptr<CaveGoblin> area = std::shared_ptr<CaveGoblin>(new CaveGoblin());
	area->generate();
	return area;
}
std::shared_ptr<Dialog> const &QuestTheGoblinKing::PhaseInCave::getDialog(Creature &owner){
	return QuestPhase::getDialog(owner);
}
TradeContainer &QuestTheGoblinKing::PhaseInCave::getTradeContainer(Creature &owner){
	return QuestPhase::getTradeContainer(owner);
}

