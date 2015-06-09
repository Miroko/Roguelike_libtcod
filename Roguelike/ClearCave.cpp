#include "ClearCave.h"
#include "Engine.h"
#include "Goblin.h"
#include "Forest.h"
#include "Cave.h"

void ClearCave::WayToCave::generateArea(Area &area){
	area = Forest(100, 10, 100);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		if (area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}	
}

void ClearCave::CaveEntrance::generateArea(Area &area){
	area = Forest(100, 20, 30);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		if (area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}
}

void ClearCave::InTheCave::generateArea(Area &area){
	area = Cave(100, 0.2, 3, 0.10, 3);
	
	for (int creatures = 30; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		if (area.placeAliveObject(creature, p)){
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
