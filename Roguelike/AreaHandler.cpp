#include "AreaHandler.h"
#include "Engine.h"

void AreaHandler::setCurrentArea(std::shared_ptr<Area> area){
	currentArea = area;
}

void AreaHandler::updateArea(){
	currentArea->update();
	if (engine::playerHandler.getPlayerCreature()->isDead){
		engine::playerHandler.getPlayerCreature()->isDead = false;
		engine::playerHandler.getPlayerCreature()->health = engine::playerHandler.getPlayerCreature()->healthMax;
		engine::questHandler.travelToVillage();
	}
	else{
		currentArea->cleanDeadDynamicObjects();
	}
}

void AreaHandler::renderArea(){
	currentArea->render();
}

std::shared_ptr<Area> &AreaHandler::getCurrentArea(){
	return currentArea;
}