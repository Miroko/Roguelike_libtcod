#include "AreaHandler.h"
#include "Quest.h"
#include "Engine.h"

void AreaHandler::setCurrentArea(std::shared_ptr<Area> area){
	currentArea = area;
}
std::shared_ptr<Area> &AreaHandler::getCurrentArea(){
	return currentArea;
}
void AreaHandler::saveCurrentArea(){
	savedPhaseAreas.push_back(std::make_pair(engine::questHandler.getCurrentQuest().get()->currentPhase, currentArea));
}
bool AreaHandler::loadSavedArea(std::shared_ptr<QuestPhase> persistentPhase){
	for (auto &savedPhaseArea : savedPhaseAreas){
		if (savedPhaseArea.first == persistentPhase){
			currentArea = savedPhaseArea.second;
			return true;
		}
	}
	return false;
}

void AreaHandler::updateArea(){
	currentArea->update();
}

void AreaHandler::cleanDeadObjects(){
	currentArea->cleanDeadDynamicObjects();
}

void AreaHandler::renderArea(){
	currentArea->render();
}

