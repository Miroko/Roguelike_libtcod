#include "AreaDrop.h"
#include "Engine.h"

void AreaDrop::drop(Point2D &location, int dropAreaSize, Area &area){
	Rectangle areaToDropIn = Rectangle(location, location);
	areaToDropIn.expand(dropAreaSize);
	for (auto &creature : creaturesRarityChance){
		if (engine::random.chance(creature.second.second)){
			auto &createdCreature = engine::objectFactory.createCreature(creature.first, creature.second.first);
			area.placeCreature(createdCreature, engine::random.point(areaToDropIn));			
		}
	}
	for (auto &operatable : operatablesRarityChance){
		if (engine::random.chance(operatable.second.second)){
			auto &operatableCreated = engine::objectFactory.createOperatable(operatable.first, operatable.second.first);
			area.placeOperatable(operatableCreated, engine::random.point(areaToDropIn));
		}
	}
}