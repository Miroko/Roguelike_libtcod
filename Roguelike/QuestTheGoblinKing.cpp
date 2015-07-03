#include "QuestTheGoblinKing.h"
#include "Forest.h"
#include "Engine.h"

//Forest
void QuestTheGoblinKing::ForestGoblin::onGatePlace(Point2D &location){

}

void QuestTheGoblinKing::ForestGoblin::onStonePlaced(Point2D &location){

}

//Village phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseVillage::generateArea(){
	std::shared_ptr<ForestGoblin> area = std::shared_ptr<ForestGoblin>(new ForestGoblin());
	area->generate();
	
	int drops = area->getBounds().getSize() / 500;
	for (int drop = drops; drop > 0; --drop){
		Point2D location = engine::random.point(area->getBounds());
		area->dropGoblin.drop(location, *area);
	}

	return area;
}
std::shared_ptr<Dialog> const &QuestTheGoblinKing::PhaseVillage::getDialog(DynamicObject &owner){
	return QuestPhase::getDialog(owner);
}
std::shared_ptr<TradeContainer> const &QuestTheGoblinKing::PhaseVillage::getTradeContainer(DynamicObject &owner){
	return nullptr;
}

//Forest phase
std::shared_ptr<Area> QuestTheGoblinKing::PhaseWayThroughForest::generateArea(){
	std::shared_ptr<ForestGoblin> area = std::shared_ptr<ForestGoblin>(new ForestGoblin());
	area->generate();
	return area;
}
std::shared_ptr<Dialog> const &QuestTheGoblinKing::PhaseWayThroughForest::getDialog(DynamicObject &owner){
	return QuestPhase::getDialog(owner);
}
std::shared_ptr<TradeContainer> const &QuestTheGoblinKing::PhaseWayThroughForest::getTradeContainer(DynamicObject &owner){
	return nullptr;
}
