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
	//save area if persistent
	if (currentQuest->currentPhase != nullptr){
		if (currentQuest->currentPhase->persistent){
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
		//if not persistent or saved generate new area
		engine::areaHandler.setCurrentArea(phase->generateArea());
	}
	//remove player from current area
	auto &areaCreatures = engine::areaHandler.getCurrentArea()->creatures;
	auto &creatureIterator = areaCreatures.begin();
	while (creatureIterator != areaCreatures.end()){
		if (creatureIterator->get() == engine::playerHandler.getPlayerCreature().get()){
			areaCreatures.erase(creatureIterator);
			break;
		}
		++creatureIterator;
	}
	//place player to new area
	engine::areaHandler.getCurrentArea()->placeCreature(
		engine::playerHandler.getPlayerCreature(),
		engine::areaHandler.getCurrentArea()->getBounds().getCenterPoint());

	if (!loaded){
		engine::areaHandler.getCurrentArea()->initAi();
	}
	else{
		//ai already initialized
		//only update player fov
		engine::playerHandler.getPlayerCreature()->ai->initAi(
			*engine::playerHandler.getPlayerCreature(),
			*engine::areaHandler.getCurrentArea());
	}

	engine::camera.centerOn(engine::playerHandler.getPlayerCreature()->location);
}
void QuestHandler::travelToNextPhase(){
	travelToPhase(currentQuest->getNextPhase());
}
void QuestHandler::travelToVillage(){
	travelToPhase(currentQuest->getVillage());
	currentQuest->currentPhaseIndex = 0;
}
