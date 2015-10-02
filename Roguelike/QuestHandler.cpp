#include "QuestHandler.h"
#include "Quest.h"
#include "Engine.h"

void QuestHandler::setCurrentQuest(std::shared_ptr<Quest> quest){
	currentQuest = quest;
	engine::gui.log.addMessage("New quest: " + currentQuest->name);
}
std::shared_ptr<Quest> const &QuestHandler::getCurrentQuest(){
	return currentQuest;
}
void QuestHandler::travelToPhase(std::shared_ptr<QuestPhase> const &phase){
	auto &playerCreature = engine::playerHandler.getPlayerCreature();
	//save area if persistent
	if (currentQuest->currentPhase){
		if (currentQuest->currentPhase->persistent){
			//destroy player from area before saving
			engine::areaHandler.getCurrentArea()->destroyDynamicObject(*playerCreature);
			engine::areaHandler.getCurrentArea()->cleanDeadObjects();
			engine::areaHandler.saveCurrentArea();
		}
	}
	//set next area, load if saved
	currentQuest->setCurrentPhase(phase);
	bool loaded = false;
	if (phase->persistent){
		loaded = engine::areaHandler.loadSavedArea(phase);
	}
	if (!loaded){
		//generate new area
		engine::areaHandler.setCurrentArea(phase->generateArea());
	}
	//place player to new area
	engine::areaHandler.getCurrentArea()->placeCreature(playerCreature, engine::areaHandler.getCurrentArea()->getBounds().getCenterPoint());
	engine::camera.centerOn(playerCreature->location);
	if (loaded){
		playerCreature->initAi(*engine::areaHandler.getCurrentArea());
	}
	else{
		engine::areaHandler.getCurrentArea()->initAi();
	}
}
void QuestHandler::travelToNextPhase(){
	travelToPhase(currentQuest->getNextPhase());
}
void QuestHandler::travelToVillage(){
	travelToPhase(currentQuest->getVillage());
	currentQuest->currentPhaseIndex = 0;
}
