#include "AreaHandler.h"

void AreaHandler::setCurrentArea(std::shared_ptr<Area> area){
	currentArea = area;
}

void AreaHandler::updateArea(){
	currentArea->update();
	currentArea->cleanDeadDynamicObjects();
}

void AreaHandler::renderArea(){
	currentArea->render();
}

std::shared_ptr<Area> &AreaHandler::getCurrentArea(){
	return currentArea;
}