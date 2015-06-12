#include "TheGoblinKing.h"
#include "Engine.h"
#include "Goblin.h"
#include "Forest.h"
#include "Cave.h"
#include "Portal.h"

void TheGoblinKing::WayToCave::generateArea(Area &area){
	area = Forest(100, 10, 100);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		if (area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}

	for (int portals = 12; portals > 0; portals--){
		Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE); //Prefer min and max values

		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(FOREST_PORTAL);
		area.placePortal(portal, p);

		Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR); //back to normal
	}
}

bool TheGoblinKing::WayToCave::winCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerHandler.playerCreature->location == portal->location){
			return true;
		}
	}
	return false;
}

void TheGoblinKing::CaveEntrance::generateArea(Area &area){
	area = Forest(100, 20, 30);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		if (area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}

	for (int portals = 6; portals > 0; portals--){
		Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);

		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(CAVE_PORTAL);
		area.placePortal(portal, p);

		Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR);
	}
}

bool TheGoblinKing::CaveEntrance::winCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerHandler.playerCreature->location == portal->location){
			return true;
		}
	}
	return false;
}

void TheGoblinKing::InTheCave::generateArea(Area &area){
	area = Cave(100, 0.2, 3, 0.10, 3);
	
	for (int creatures = 30; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		if (area.placeAliveObject(creature, p)){
			creature->setTarget(Engine::playerHandler.playerCreature.get());
		}
	}	
}

bool TheGoblinKing::InTheCave::winCondition(){
	return false;
}

std::shared_ptr<QuestPhase> TheGoblinKing::getNextPhase(){
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
