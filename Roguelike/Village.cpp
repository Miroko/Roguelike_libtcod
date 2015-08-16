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
	std::string stoneHighId,
	std::string stoneLowId,
	std::string pathId,
	int size,
	std::vector<std::pair<AreaHouse*, double>> houseChances) :
	Area(),
	size(size),
	land(*engine::objectLibrary.tiles[landId]),
	tree(*engine::objectLibrary.tiles[treeId]),
	stoneHigh(*engine::objectLibrary.tiles[stoneHighId]),
	stoneLow(*engine::objectLibrary.tiles[stoneLowId]),
	path(*engine::objectLibrary.tiles[pathId]),
	houseChances(houseChances){
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
			offsetX = engine::random.generator->getInt(4, 8);
			offsetY = engine::random.generator->getInt(4, 8);
			plotSize = engine::random.generator->getInt(5, 8);
			Rectangle plot = Rectangle(
				Point2D(x + offsetX, y + offsetY),
				Point2D(x + plotSize + offsetX, y + plotSize + offsetY));
			if (!plot.contains(villageBounds.getCenterPoint())){
				int randomIndex = engine::random.generator->getInt(0, houseChances.size() - 1);
				auto &houseChance = houseChances.at(randomIndex);
				if (engine::random.generator->getFloat(0.0f, 1.0f) < houseChance.second){
					houseChance.first->build(plot, *this);
					houses.push_back(*houseChance.first);
				}
			}
			y += plotSize + offsetY;
			if (largestPlot < plotSize + offsetX) largestPlot = plotSize + offsetX;
		}
		x += largestPlot;
	}

	//build roads to houses in random order
	//road build block tiles
	std::vector<Tile*> blockTiles;
	for (auto &house : houses){
		bool add = true;
		for (auto &tile : blockTiles){
			if (&house.wall == tile){
				add = false;
				break;
			}
		}
		if (add){
			blockTiles.push_back(&house.wall);
		}
	}
	blockTiles.push_back(&stoneHigh);
	//road build overlay tiles
	std::vector<Tile*> overlayTiles;
	for (auto &house : houses){
		bool add = true;
		for (auto &tile : overlayTiles){
			if (&house.floor == tile){
				add = false;
				break;
			}
		}
		if (add){
			overlayTiles.push_back(&house.floor);
		}
	}

	AreaPath pathBuilder = AreaPath(path, *this, blockTiles, overlayTiles, 0.1f, 1, 0);
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

	//place stones
	int stones = (int)(getBounds().getSize() * 0.010);
	for (int stoneNumber = stones; stoneNumber > 0; --stoneNumber){
		Point2D location = engine::random.point(getBounds());
		placeTile(stoneHigh, location, land);

		Rectangle surrounding = Rectangle(location, location);
		surrounding.expand(2);
		for (int lowStone = engine::random.generator->getInt(1, 4); lowStone > 0; lowStone--){
			Point2D location = engine::random.point(surrounding);
			placeTile(stoneLow, location, land);
		}
	}

	//village center
	Rectangle center = villageBounds;
	center.shrink(size / 4);
	for (int centerSize = villageBounds.getSize() / 25; centerSize > 0; --centerSize){
		Point2D placeLocation = engine::random.point(center);
		placeTile(path, placeLocation, land);
	}

	//place trees
	//use road build block tiles with additions
	for (auto &house : houses){
		bool add = true;
		for (auto &tile : blockTiles){
			if (&house.floor == tile){
				add = false;
				break;
			}
		}
		if (add){
			blockTiles.push_back(&house.floor);
		}
	}
	blockTiles.push_back(&path);
	int trees = (int)(getBounds().getSize() * 0.10f);
	int treesPerSpot = 5;
	int spots = trees / treesPerSpot;
	for (int spot = spots; spot > 0; --spot){
		Point2D landSpot = getNearestTile(engine::random.point(getBounds()), land);
		AreaTreeSpot treeSpot = AreaTreeSpot(tree, treesPerSpot, 1, landSpot, blockTiles);
		treeSpot.grow(*this);
	}	
	//place trees on edges
	generateEdge(tree, size / 5, 12);
}