#include "ClearCave.h"
#include "Engine.h"
#include "goblin.h"

void ClearCave::WayToCave::generateArea(Area &area){
	area = Area(100, LAND);
	
	int trees = area.bounds.getSize() / 10;
	for (int tree = trees; tree > 0; tree--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		area.setStaticObject(TREE, p);
	}
	
	int rocks = area.bounds.getSize() / 100;
	for (int rock = rocks; rock > 0; rock--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		area.setStaticObject(STONE, p);
	}

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = std::shared_ptr<AliveObject>(new race::goblin::GoblinBase(race::goblin::GOBLIN_BASE));
		if (Engine::area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}
	
}

void ClearCave::CaveEntrance::generateArea(Area &area){
	area = Area(100, LAND);

	int trees = area.bounds.getSize() / 20;
	for (int tree = trees; tree > 0; tree--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		area.setStaticObject(TREE, p);
	}

	int rocks = area.bounds.getSize() / 30;
	for (int rock = rocks; rock > 0; rock--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		area.setStaticObject(STONE, p);
	}

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = std::shared_ptr<AliveObject>(new race::goblin::GoblinBase(race::goblin::GOBLIN_BASE));
		if (Engine::area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}
}

void ClearCave::InTheCave::generateArea(Area &area){
	area = Area(50, STONE_FLOOR);

	int pathLenght = area.bounds.getSize() / 10;
	int roomAmount = area.bounds.getSize() / 50;
	Point2D currentPoint = area.bounds.getCenterPoint();
	while (pathLenght > 0){

		--pathLenght;
	}


	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = std::shared_ptr<AliveObject>(new race::goblin::GoblinBase(race::goblin::GOBLIN_BASE));
		if (Engine::area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}
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
