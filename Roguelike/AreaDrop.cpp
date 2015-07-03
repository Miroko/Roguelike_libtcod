#include "AreaDrop.h"
#include "Engine.h"

void AreaDrop::drop(Point2D &location, Area &area){
	Rectangle areaToDropIn = Rectangle(location, location);
	areaToDropIn.expand(2);
	for (auto &creature : creaturesRarityChance){
		if (engine::random.generator->getFloat(0.0f, 1.0f) < creature.second.second){
			auto &createdCreature = engine::objectFactory.createCreaturePreset(creature.first, *engine::objectLibrary.getRarity(creature.second.first));
			if (createdCreature != nullptr){
				area.placeCreature(createdCreature, engine::random.point(areaToDropIn));
			}
		}
	}
}