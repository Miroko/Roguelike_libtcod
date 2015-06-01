#include "Quest.h"

void ClearCave::WayToCave::generateArea(Area &area){
	area = Area(50, LAND);

	int trees = area.bounds.getSize() / 10;
	for (int tree = 0; tree < trees; tree++){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		area.setStaticObject(TREE, p);
	}
}

void ClearCave::CaveEntrance::generateArea(Area &area){
	area = Area(30, LAND);
	/*
	int trees = area.bounds.getSize() / 20;
	for (int tree = 0; tree < trees; tree++){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		area.setStaticObject(TREE, p);
	}
	*/
}

void ClearCave::InTheCave::generateArea(Area &area){
	area = Area(50, LAND);
}

std::shared_ptr<QuestPhase> ClearCave::getNextPhase(){
	if (currentPhase == nullptr){
		currentPhase = std::shared_ptr<QuestPhase>(new WayToCave());
	}
	else if (typeid(*currentPhase.get()) == typeid(WayToCave)){
		currentPhase = std::shared_ptr<QuestPhase>(new CaveEntrance());
	}
	else if (typeid(*currentPhase.get()) == typeid(CaveEntrance)){
		currentPhase = std::shared_ptr<QuestPhase>(new InTheCave());
	}
	else{
		currentPhase = std::shared_ptr<QuestPhase>(new WayToCave());
	}
	return currentPhase;
}