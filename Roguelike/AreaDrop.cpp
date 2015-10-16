#include "AreaDrop.h"
#include "AreaDen.h"
#include "Direction.h"
#include "Engine.h"

void AreaDrop::drop(Rectangle &dropBounds, Area &area){
	for (auto &creature : creaturesRarityChance){
		if (engine::random.chance(creature.second.second)){
			auto &createdCreature = engine::objectFactory.createCreature(creature.first, creature.second.first);
			area.placeCreature(createdCreature, engine::random.point(dropBounds));
		}
	}
	for (auto &operatable : operatablesRarityChance){
		if (engine::random.chance(operatable.second.second)){
			auto &operatableCreated = engine::objectFactory.createOperatable(operatable.first, operatable.second.first);
			area.placeOperatable(operatableCreated, engine::random.point(dropBounds));
		}
	}
}

void AreaDrop::drop(AreaDen &toDen, Area &area){
	//operatables
	Rectangle innerBounds = Rectangle(toDen.bounds).shrink(1);
	std::vector<Point2D> innerEdgePoints = innerBounds.getEdgePoints();
	std::list<Point2D> listOValidfInnerEdgePoints = std::list<Point2D>(innerEdgePoints.begin(), innerEdgePoints.end());
	//remove locations near door
	auto location = listOValidfInnerEdgePoints.begin();
	while (location != listOValidfInnerEdgePoints.end()){
		bool erase = false;
		for (Point2D const &direction : DIRECTIONS){
			if (*location + direction == toDen.doorLocation){
				erase = true;
			}
		}
		if (erase) location = listOValidfInnerEdgePoints.erase(location);
		else ++location;
	}
	//place operatables randomly on valid locations
	for (auto &furnitureChance : operatablesRarityChance){
		if (engine::random.chance(furnitureChance.second.second)){
			if (listOValidfInnerEdgePoints.empty()) break;
			int randomIndex = engine::random.generator->getInt(0, listOValidfInnerEdgePoints.size() - 1);
			auto &location = listOValidfInnerEdgePoints.begin();
			std::advance(location, randomIndex);
			area.placeOperatable(engine::objectFactory.createOperatable(furnitureChance.first, furnitureChance.second.first), *location);
			listOValidfInnerEdgePoints.remove(*location);
		}
	}
	//place creatures
	for (auto &creature : creaturesRarityChance){
		if (engine::random.chance(creature.second.second)){
			auto &createdCreature = engine::objectFactory.createCreature(creature.first, creature.second.first);
			area.placeCreature(createdCreature, engine::random.point(innerBounds));
		}
	}
}
