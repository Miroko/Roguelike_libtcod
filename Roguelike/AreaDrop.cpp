#include "AreaDrop.h"
#include "Engine.h"

void AreaDrop::drop(Point2D &location, int dropAreaSize, Area &area){
	Rectangle areaToDropIn = Rectangle(location, location);
	areaToDropIn.expand(dropAreaSize);
	for (auto &creature : creaturesRarityChance){
		if (engine::random.generator->getFloat(0.0f, 1.0f) <= creature.second.second){
			auto &createdCreature = engine::objectFactory.createCreature(creature.first, creature.second.first);
			if (createdCreature != nullptr){
				area.placeCreature(createdCreature, engine::random.point(areaToDropIn));
			}
		}
	}
}