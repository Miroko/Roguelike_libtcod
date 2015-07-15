#include "AreaHandler.h"
#include "Engine.h"

void AreaHandler::setCurrentArea(std::shared_ptr<Area> area){
	currentArea = area;
}
std::shared_ptr<Area> &AreaHandler::getCurrentArea(){
	return currentArea;
}
void AreaHandler::saveCurrentArea(){
	savedArea = currentArea;
}
void AreaHandler::loadSavedArea(){
	currentArea = savedArea;
}

void AreaHandler::updateArea(){
	currentArea->update();
	if (engine::playerHandler.getPlayerCreature()->isDead){
		engine::newGame();
	}
	else{
		currentArea->cleanDeadDynamicObjects();
	}
}
void AreaHandler::renderArea(){
	currentArea->render();
}

