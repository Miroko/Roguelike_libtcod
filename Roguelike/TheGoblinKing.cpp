#include "TheGoblinKing.h"
#include "Engine.h"
#include "Goblin.h"
#include "Forest.h"
#include "Cave.h"
#include "Portal.h"
#include "Village.h"
#include "Human.h"

bool TheGoblinKing::storyTold = false;

TheGoblinKing::TheGoblinKing() : Quest("The Goblin King"){
	tradeContainerVillage = std::shared_ptr<TradeContainer>(new TradeContainer(
		30,
		std::vector<std::shared_ptr<Item>>({
		Item::newItem(SWORD),
		Item::newItem(HEALTH_POTION),
		Item::newItem(HEALTH_POTION)
	})));
	storyTold = false;
}

void TheGoblinKing::WayToCave::generateArea(Area &area){
	area = Forest(100, 10, 100);

	for (int creatures = 20; creatures > 0; creatures--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<AliveObject> creature = Creature::newCreature(GOBLIN);
		area.placeAliveObject(creature, p);
		creature->setTarget(Engine::playerController.playerCreature);
	}

	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE); //Prefer min and max values
	for (int portals = 12; portals > 0; portals--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(FOREST_PORTAL);
		area.placePortal(portal, p);
	}
	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR); //back to normal
}

bool TheGoblinKing::WayToCave::winCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerController.playerCreature->location == portal->location){
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
			creature->setTarget(Engine::playerController.playerCreature);
		}
	}

	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);
	for (int portals = 6; portals > 0; portals--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(CAVE_PORTAL);
		area.placePortal(portal, p);
	}
	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR);
}

bool TheGoblinKing::CaveEntrance::winCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerController.playerCreature->location == portal->location){
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
			creature->setTarget(Engine::playerController.playerCreature);
		}
	}	
}

bool TheGoblinKing::InTheCave::winCondition(){
	return false;
}

void TheGoblinKing::InVillage::generateArea(Area &area){
	Random::useStatic();

	Village villageArea = Village();
	area = villageArea;

	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);
	for (int portals = 20; portals > 0; portals--){
		Point2D p = Point2D(Random::generator.getInt(0, area.bounds.getWidth() - 1), Random::generator.getInt(0, area.bounds.getHeight() - 1));
		std::shared_ptr<Portal> portal = Portal::newPortal(FOREST_PORTAL);
		if (!villageArea.villageBounds.inside(p)){
			area.placePortal(portal, p);
		}
	}
	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR);

	Random::useRandom();
}

bool TheGoblinKing::InVillage::winCondition(){
	for (auto &portal : Engine::area.portals){
		if (Engine::playerController.playerCreature->location == portal->location){
			return true;
		}
	}
	return false;
}


std::shared_ptr<QuestPhase> TheGoblinKing::getNextPhase(){
	if (typeid(*currentPhase.get()) == typeid(InVillage)){
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

std::shared_ptr<QuestPhase> TheGoblinKing::getVillage(){
	return std::shared_ptr<QuestPhase>(new InVillage());
}

std::shared_ptr<Dialog> TheGoblinKing::getDialog(std::shared_ptr<DynamicObject> &owner){
	Human *human = dynamic_cast<Human*>(owner.get());
	if (human != nullptr){
		if (!storyTold) return std::shared_ptr<Dialog>(new DialogVillagerStory1(owner));
		else return std::shared_ptr<Dialog>(new DialogVillagerTrade(owner));
	}
	else return Quest::getDialog(owner);
}

std::shared_ptr<TradeContainer> TheGoblinKing::getTradeContainer(std::shared_ptr<DynamicObject> &owner){
	Human *human = dynamic_cast<Human*>(owner.get());
	if (human != nullptr){
		return tradeContainerVillage;
	}
	else return nullptr;
}