#include "QuestHandler.h"
#include "Engine.h"

void QuestHandler::setCurrentQuest(std::shared_ptr<Quest> quest){
	Random::reset();
	currentQuest = quest;
	Engine::GUI.log.addMessage("Quest added: " + quest->name);
}

void QuestHandler::generateNextPhase(){
	currentQuest->getNextPhase()->generateArea(Engine::area);

	Engine::area.placeAliveObject(Engine::playerController.playerCreature, Engine::area.bounds.getCenterPoint());
	Engine::camera.centerOn(Engine::playerController.playerCreature->location);
}

void QuestHandler::toVillage(){
	currentQuest->currentPhase = currentQuest->getVillage();
	currentQuest->currentPhase->generateArea(Engine::area);

	Engine::area.placeAliveObject(Engine::playerController.playerCreature, Engine::area.bounds.getCenterPoint());
	Engine::camera.centerOn(Engine::playerController.playerCreature->location);
}

void QuestHandler::update(){
	if (currentQuest->currentPhase->winCondition()){
		generateNextPhase();
	}
}