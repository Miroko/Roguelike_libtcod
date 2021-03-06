#include "QuestTheGoblinKing.h"
#include "Forest.h"
#include "Engine.h"
#include "Weapon.h"

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

	blacksmithTradeContainer.generateItems();
	alchemistTradeContainer.generateItems();

	return area;
}
std::shared_ptr<Dialog> const &QuestTheGoblinKing::PhaseVillage::getDialog(Creature &speaker){
	if (speaker.presetId == "villager_blacksmith"){
		dialogBlacksmith->setSpeaker(speaker);
		return dialogBlacksmith;
	}
	else if (speaker.presetId == "villager_alchemist"){
		dialogAlchemist->setSpeaker(speaker);
		return dialogAlchemist;
	}
	else return QuestPhase::getDialog(speaker);
}
TradeContainer &QuestTheGoblinKing::PhaseVillage::getTradeContainer(Creature &trader){
	if (trader.presetId == "villager_blacksmith"){
		return blacksmithTradeContainer;
	} 
	else if (trader.presetId == "villager_alchemist"){
		return alchemistTradeContainer;
	}
	else return QuestPhase::getTradeContainer(trader);
}

//Forest phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseWayThroughForest::generateArea(){
	std::shared_ptr<ForestGoblin> area = std::shared_ptr<ForestGoblin>(new ForestGoblin());
	area->generate();
	return area;
}

//Cave phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseInCave::generateArea(){
	std::shared_ptr<CaveGoblin> area = std::shared_ptr<CaveGoblin>(new CaveGoblin());
	area->generate();
	return area;
}

//King phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseKing::generateArea(){
	std::shared_ptr<CaveKing> area = std::shared_ptr<CaveKing>(new CaveKing());
	area->generate();

	Point2D dropLocation = engine::random.point(area->getBounds());
	area->dropKing.drop(Rectangle(dropLocation, 1), *area);

	return area;
}
