#include "Container.h"
#include "Engine.h"

void Container::dropLoot(Creature &looter){
	if (!opened){
		auto &possibleDropLocations = engine::areaHandler.getCurrentArea()->getOpenTiles(Rectangle(location, 1));
		auto& lootDrop = engine::objectFactory.generateLootDrop(lootDropsFromMax, *rarityType);
		if (!possibleDropLocations.empty()){
			for (auto &loot : lootDrop){
				Point2D dropLocation = possibleDropLocations.at(engine::random.generator->get(0, possibleDropLocations.size() - 1));
				engine::areaHandler.getCurrentArea()->placeItem(loot, dropLocation);
			}
		}
		else{
			for (auto &loot : lootDrop){
				engine::areaHandler.getCurrentArea()->placeItem(loot, location);
			}
		}
		opened = true;
	}
}

void Container::operate(Creature &user){
	if (!opened){
		glyph = openGlyph;
		dropLoot(user);
		OperatableObject::operate(user);
	}
}

bool Container::isPassable(DynamicObject &dynamicObject){
	return !isLarge;
}

void Container::onDeath(){
	dropLoot(*engine::playerHandler.getPlayerCreature());
	OperatableObject::onDeath();
}

std::shared_ptr<OperatableObject> Container::copy(){
	return std::shared_ptr<OperatableObject>(new Container(*this));
}

