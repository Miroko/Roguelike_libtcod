#include "Village.h"
#include "Creature.h"
#include "Engine.h"
#include "AreaHouse.h"
#include "AreaTreeSpot.h"
#include "AreaPath.h"
#include "AreaDrop.h"

Village::Village(
	std::string landId,
	std::string treeId,
	std::string houseWallId,
	std::string houseFloorId,
	std::string pathId,
	std::string doorId,
	int size,
	AreaDrop &residents) :
	Area(),
	size(size),
	land(*engine::objectLibrary.getTile(landId)),
	tree(*engine::objectLibrary.getTile(treeId)),
	houseWall(*engine::objectLibrary.getTile(houseWallId)),
	houseFloor(*engine::objectLibrary.getTile(houseFloorId)),
	path(*engine::objectLibrary.getTile(pathId)),
	doorId(doorId),
	residents(residents){
}

void Village::generate(){
	generateBase(Rectangle(size, size), land);

	//calculate village area
	villageBounds = Rectangle(getBounds());
	villageBounds.shrink(size / 5);

	//build houses
	int plotSize = plotSize = engine::random.generator->getInt(3, 12);
	int largestPlot = 0;
	int offsetX = 0;
	int offsetY = 0;
	for (int x = villageBounds.start.x; x < villageBounds.end.x - largestPlot;){
		for (int y = villageBounds.start.y; y < villageBounds.end.y - largestPlot;){
			offsetX = engine::random.generator->getInt(4, 6);
			offsetY = engine::random.generator->getInt(4, 6);
			plotSize = engine::random.generator->getInt(7, 12);
			Rectangle plot = Rectangle(
				Point2D(x + offsetX, y + offsetY),
				Point2D(x + plotSize + offsetX, y + plotSize + offsetY));
			if (!plot.contains(villageBounds.getCenterPoint())){
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.8f){
					houses.push_back(AreaHouse(houseWall, houseFloor, plot));
				}
			}
			y += plotSize + offsetY;
			if (largestPlot < plotSize + offsetX) largestPlot = plotSize + offsetX;
		}
		x += largestPlot;
	}
	for (AreaHouse house : houses){
		house.build(engine::objectFactory.createDoor(doorId), residents, *this);
	}

	//village center
	for (int centerSize = villageBounds.getSize() / 30; centerSize > 0; --centerSize){
		placeTile(path, villageBounds.getCenterPoint(), land);
	}

	//build roads to houses in random order
	AreaPath pathBuilder = AreaPath(path, *this, { &houseWall }, houseFloor);
	std::vector<int> randomIndexes;
	while (randomIndexes.size() < houses.size()){
		int randomIndex = engine::random.generator->getInt(0, houses.size() - 1);
		bool unique = true;
		for (int index : randomIndexes){
			if (index == randomIndex){
				unique = false;
				break;
			}
		}
		if (unique) randomIndexes.push_back(randomIndex);
	}
	for (int index : randomIndexes){
		pathBuilder.build(getBounds().getCenterPoint(), houses.at(index).bounds.getCenterPoint());
	}

	//place trees in village
	int trees = (int)(getBounds().getSize() * 0.05f);
	int treesPerSpot = 10;
	int spots = trees / treesPerSpot;
	for (int spot = spots; spot > 0; --spot){
		Point2D landSpot = getNearestTile(engine::random.point(villageBounds), land);
		AreaTreeSpot treeSpot = AreaTreeSpot(tree, treesPerSpot, 1, landSpot, {&houseFloor, &houseWall, &path});
		treeSpot.grow(*this);
	}
	
	//place trees on edges
	generateEdge(tree, size / 6, 12);
}

/*

//Villager
Rectangle villagerArea = Rectangle(Point2D(plot.start.x + 1, plot.start.y + 1),
Point2D(plot.end.x, plot.end.y));
int villagers = Random::generator->getInt(1, 3, 1);
for (int villager = villagers; villager > 0; villager--){
Point2D location = Random::point(villagerArea);
std::shared_ptr<Creature> man = ObjectLibrary::generateCreature(
ObjectLibrary::MAN,
RarityType::COMMON,
ObjectLibrary::MAN_EQUIPMENT,
ObjectLibrary::MAN_LOOT);
man->ai.state = CreatureAi::FREE;
placeCreature(man, location);
}


//Door
Point2D doorPoint = points.at(Random::generator->getInt(0, points.size() - 1));
setStaticObject(ObjectLibrary::WOOD_FLOOR, doorPoint);
placeOperatable(ObjectLibrary::generateDoor(ObjectLibrary::WOOD_DOOR, ObjectLibrary::DOOR_LOOT), doorPoint);
*/