#include "QuestHandler.h"
#include "Engine.h"

void QuestHandler::addQuest(Quest *quest){
	quests.push_back(std::shared_ptr<Quest>(quest));
	Engine::log.addMessage("Quest added");
}
void QuestHandler::setCurrentQuest(Quest *quest){
	currentQuest = quest;
}
void QuestHandler::generateNextPhase(){
	currentQuest->getNextPhase()->generateArea(Engine::area);
	
	// Place player
	Engine::area.placeAliveObject(Engine::playerHandler.playerObject, Engine::area.bounds.getCenterPoint());
	Engine::camera.centerOn(Engine::playerHandler.playerObject->location);

	// Test alive objects
	for (int a = 0; a < 10; a++){
		std::shared_ptr<AliveObject> testHuman = std::shared_ptr<AliveObject>(new Human("Human " + std::to_string(a)));
		if (Engine::area.placeAliveObject(testHuman, Point2D(15, 15 + 2*a))){
			testHuman->setTarget(Engine::playerHandler.playerObject.get());
			testHuman->weapon = &testHuman->loot->weapons[0];
		}
	}
}
