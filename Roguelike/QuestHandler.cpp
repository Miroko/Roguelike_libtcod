#include "QuestHandler.h"
#include "Quest.h"
#include "Engine.h"

void QuestHandler::setCurrentQuest(std::shared_ptr<Quest> quest){
	currentQuest = quest;
}
std::shared_ptr<Quest> const &QuestHandler::getCurrentQuest(){
	return currentQuest;
}
void QuestHandler::travelToPhase(std::shared_ptr<QuestPhase> const &phase){
	currentQuest->setCurrentPhase(phase);
	engine::areaHandler.setCurrentArea(phase->generateArea());
	engine::areaHandler.getCurrentArea()->placeCreature(
		engine::playerHandler.getPlayerCreature(),
		engine::areaHandler.getCurrentArea()->getBounds().getCenterPoint());
	engine::camera.centerOn(engine::playerHandler.getPlayerCreature()->location);
	engine::areaHandler.getCurrentArea()->initAi();
}
void QuestHandler::travelToNextPhase(){
	travelToPhase(currentQuest->getNextPhase());
}
void QuestHandler::travelToVillage(){
	travelToPhase(currentQuest->getVillage());
	currentQuest->currentPhaseIndex = 0;
}
