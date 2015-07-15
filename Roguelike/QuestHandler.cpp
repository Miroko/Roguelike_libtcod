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
	engine::areaHandler.getCurrentArea()->initAi();

	engine::camera.centerOn(engine::playerHandler.getPlayerCreature()->location);
}
void QuestHandler::travelToNextPhase(){
	if (currentQuest->getCurrentPhase() == currentQuest->getVillage()){
		engine::areaHandler.saveCurrentArea();
	}
	travelToPhase(currentQuest->getNextPhase());
}
void QuestHandler::travelToVillage(){
	if (currentQuest->getCurrentPhase() != currentQuest->getVillage()){
		if (engine::areaHandler.savedArea != nullptr){
			engine::areaHandler.loadSavedArea();

			engine::areaHandler.getCurrentArea()->placeCreature(
				engine::playerHandler.getPlayerCreature(),
				engine::areaHandler.getCurrentArea()->getBounds().getCenterPoint());

			engine::playerHandler.getPlayerCreature()->ai->initAi(
				*engine::playerHandler.getPlayerCreature(),
				*engine::areaHandler.getCurrentArea());
			engine::camera.centerOn(engine::playerHandler.getPlayerCreature()->location);
		}
		else{
			travelToPhase(currentQuest->getVillage());
		}
		currentQuest->setCurrentPhase(currentQuest->getVillage());
		currentQuest->currentPhaseIndex = 0;
	}
}
