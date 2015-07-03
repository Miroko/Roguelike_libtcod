#include "QuestHandler.h"
#include "Quest.h"
#include "Engine.h"

void QuestHandler::setCurrentQuest(std::shared_ptr<Quest> quest){
	currentQuest = quest;
}

std::shared_ptr<Quest> const &QuestHandler::getCurrentQuest(){
	return currentQuest;
}

void QuestHandler::travelToVillage(){
	currentQuest->setCurrentPhase(currentQuest->getVillage());
	engine::areaHandler.setCurrentArea(currentQuest->getCurrentPhase()->generateArea());

	engine::areaHandler.getCurrentArea()->placeCreature(
		engine::playerHandler.getPlayerCreature(), 
		engine::areaHandler.getCurrentArea()->getBounds().getCenterPoint());

	engine::camera.centerOn(engine::playerHandler.getPlayerCreature()->location);

	engine::areaHandler.getCurrentArea()->initAi();
}
