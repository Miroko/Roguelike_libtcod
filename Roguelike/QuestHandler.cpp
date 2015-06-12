#include "QuestHandler.h"
#include "Engine.h"

void QuestHandler::addQuest(Quest *quest){
	quests.push_back(std::shared_ptr<Quest>(quest));
	Engine::GUI.log.addMessage("Quest added: " + quest->name);
}

void QuestHandler::setCurrentQuest(Quest *quest){
	currentQuest = quest;
}

void QuestHandler::generateNextPhase(){
	currentQuest->getNextPhase()->generateArea(Engine::area);
	// Place player at center
	Engine::area.placeAliveObject(Engine::playerHandler.playerCreature, Engine::area.bounds.getCenterPoint());
	Engine::camera.centerOn(Engine::playerHandler.playerCreature->location);
}

void QuestHandler::update(){
	if (currentQuest->currentPhase->winCondition()){
		generateNextPhase();
	}
}