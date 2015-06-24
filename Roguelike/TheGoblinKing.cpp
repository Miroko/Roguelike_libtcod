#include "TheGoblinKing.h"
#include "Engine.h"
#include "Goblin.h"
#include "Forest.h"
#include "Cave.h"
#include "Portal.h"
#include "Village.h"
#include "Human.h"

const std::shared_ptr<QuestPhase> TheGoblinKing::VILLAGE = std::shared_ptr<QuestPhase>(new PhaseVillage());
const std::shared_ptr<QuestPhase> TheGoblinKing::FOREST = std::shared_ptr<QuestPhase>(new PhaseForest());;
const std::shared_ptr<QuestPhase> TheGoblinKing::NEAR_CAVE = std::shared_ptr<QuestPhase>(new PhaseNearCave());
const std::shared_ptr<QuestPhase> TheGoblinKing::CAVE = std::shared_ptr<QuestPhase>(new PhaseCave());;

bool TheGoblinKing::VILLAGE_STORY_TOLD;

std::shared_ptr<TradeContainer> TheGoblinKing::VILLAGE_TRADE_CONTAINER;

TheGoblinKing::TheGoblinKing() : Quest("The Goblin King"){
	VILLAGE_STORY_TOLD = false;

	VILLAGE_TRADE_CONTAINER = std::shared_ptr<TradeContainer>(new TradeContainer(
		30,
		std::vector<std::shared_ptr<Item>>({
		Item::newItem(SWORD),
		Item::newItem(HEALTH_POTION),
		Item::newItem(HEALTH_POTION)
	})));
}

void TheGoblinKing::PhaseForest::generateArea(Area &area){
	area = Forest(100, 10, 100);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Creature> creature = Creature::newCreature(GOBLIN, GOBLIN_EQUIPMENT);
		area.placeCreature(creature, p);
		creature->ai.setCombatTarget(*Engine::playerController.playerCreature);
		creature->ai.state = AliveObjectAi::COMBAT;
	}

	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE); //Prefer min and max values
	for (int portals = 12; portals > 0; portals--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(FOREST_PORTAL);
		area.placePortal(portal, p);
	}
	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR); //back to normal

	placePlayer();
}

bool TheGoblinKing::PhaseForest::nextPhaseCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerController.playerCreature->location == portal->location){
			return true;
		}
	}
	return false;
}

void TheGoblinKing::PhaseNearCave::generateArea(Area &area){
	area = Forest(100, 20, 30);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Creature> creature = Creature::newCreature(GOBLIN, GOBLIN_EQUIPMENT);
		area.placeCreature(creature, p);
		creature->ai.setCombatTarget(*Engine::playerController.playerCreature);
	}

	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);
	for (int portals = 6; portals > 0; portals--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(CAVE_PORTAL);
		area.placePortal(portal, p);
	}
	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR);

	placePlayer();
}

bool TheGoblinKing::PhaseNearCave::nextPhaseCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerController.playerCreature->location == portal->location){
			return true;
		}
	}
	return false;
}

void TheGoblinKing::PhaseCave::generateArea(Area &area){
	area = Cave(100, 0.2, 3, 0.10, 3);
	
	for (int creatures = 30; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Creature> creature = Creature::newCreature(GOBLIN, GOBLIN_EQUIPMENT);
		area.placeCreature(creature, p);
		creature->ai.setCombatTarget(*Engine::playerController.playerCreature);
	}	

	placePlayer();
}

bool TheGoblinKing::PhaseCave::nextPhaseCondition(){
	return false;
}

void TheGoblinKing::PhaseVillage::generateArea(Area &area){
	Random::useStatic();

	Village villageArea = Village();

	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);
	for (int portals = 20; portals > 0; portals--){
		Point2D p = Point2D(Random::generator.getInt(0, villageArea.bounds.getWidth() - 1),
			                Random::generator.getInt(0, villageArea.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(FOREST_PORTAL);
		if (!villageArea.villageBounds.inside(p)){
			villageArea.placePortal(portal, p);
		}
	}

	area = villageArea;

	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR);
	Random::useRandom();

	placePlayer();
}

bool TheGoblinKing::PhaseVillage::nextPhaseCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerController.playerCreature->location == portal->location){
			return true;
		}
	}
	return false;
}

std::shared_ptr<QuestPhase> TheGoblinKing::getNextPhase(){
	if (currentPhase == VILLAGE) return FOREST;
	if (currentPhase == FOREST) return NEAR_CAVE;
	if (currentPhase == NEAR_CAVE) return CAVE;
	if (currentPhase == CAVE) return VILLAGE;
}

std::shared_ptr<QuestPhase> TheGoblinKing::getVillage(){
	return VILLAGE;
}

std::shared_ptr<Dialog> TheGoblinKing::getDialog(std::shared_ptr<DynamicObject> &owner){
	std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(owner);
	if (human != nullptr){
		if (!VILLAGE_STORY_TOLD) return std::shared_ptr<Dialog>(new DialogVillagerStory1(owner));
		else return std::shared_ptr<Dialog>(new DialogVillagerTrade(owner));
	}
	else return Quest::getDialog(owner);
}

std::shared_ptr<TradeContainer> TheGoblinKing::getTradeContainer(std::shared_ptr<DynamicObject> &owner){
	std::shared_ptr<Human> human = std::dynamic_pointer_cast<Human>(owner);
	if (human != nullptr){
		return VILLAGE_TRADE_CONTAINER;
	}
	else return nullptr;
}