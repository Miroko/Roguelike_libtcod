#include "QuestHandler.h"
#include "Engine.h"

void QuestHandler::setCurrentQuest(std::shared_ptr<Quest> quest){
	currentQuest = quest;
	Engine::GUI.log.addMessage("Quest added: " + quest->name);
}

void QuestHandler::toNextPhase(){
	currentQuest->currentPhase = currentQuest->getNextPhase();
	currentQuest->currentPhase->generateArea(Engine::area);
	Engine::camera.centerOn(Engine::playerController.playerCreature->location);
}

void QuestHandler::toVillage(){
	currentQuest->currentPhase = currentQuest->getVillage();
	currentQuest->currentPhase->generateArea(Engine::area);
	Engine::camera.centerOn(Engine::playerController.playerCreature->location);
}

void QuestHandler::update(){
	if (currentQuest->currentPhase->nextPhaseCondition()) toNextPhase();
}