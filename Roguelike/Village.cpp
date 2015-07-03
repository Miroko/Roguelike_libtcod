
/*
#include "Village.h"
#include "Door.h"
#include "Creature.h"
#include "Engine.h"
#include "ObjectLibrary.h"

Village::Village() : Area(100, ObjectLibrary::FOREST_LAND){
	villageBounds = Rectangle(bounds);
	villageBounds.start.x += bounds.getWidth() / 4;
	villageBounds.start.y += bounds.getHeight() / 4;
	villageBounds.end.x -= bounds.getWidth() / 4;
	villageBounds.end.y -= bounds.getHeight() / 4;

	//FOREST_TREEs
	Random::generator->setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);
	int FOREST_TREEs = bounds.getSize() / 20;
	for (int FOREST_TREE = FOREST_TREEs; FOREST_TREE > 0; FOREST_TREE--){
		Point2D p = Random::point(bounds);
		if (!villageBounds.inside(p)){
			setStaticObject(ObjectLibrary::FOREST_TREE, p);
		}
	}
	Random::generator->setDistribution(TCOD_DISTRIBUTION_LINEAR);

	//House plots
	int plotSize = plotSize = Random::generator->getInt(3, 12);
	std::vector<Rectangle> plots;
	int largestPlot = 0;
	int offsetX = 0;
	int offsetY = 0;
	for (int x = villageBounds.start.x; x < villageBounds.end.x - largestPlot;){
		for (int y = villageBounds.start.y; y < villageBounds.end.y - largestPlot;){
			offsetX = Random::generator->getInt(2, 5);
			offsetY = Random::generator->getInt(2, 5);
			plotSize = Random::generator->getInt(3, 12); 
			Rectangle plot = Rectangle(Point2D(x + offsetX, y + offsetY), Point2D(x + plotSize + offsetX, y + plotSize + offsetY));
			if (!plot.contains(villageBounds.getCenterPoint())){
				plots.push_back(plot);
			}

			y += plotSize + offsetY;
			if (largestPlot < plotSize + offsetX) largestPlot = plotSize + offsetX;
		}
		x += largestPlot;
	}

	//Houses
	for (Rectangle plot : plots){
		std::vector<Point2D> points = plot.getEdgePoints();

		//Floor
		for (int x = plot.start.x + 1; x < plot.end.x; x++){
			for (int y = plot.start.y + 1; y < plot.end.y; y++){
				setStaticObject(ObjectLibrary::WOOD_FLOOR, Point2D(x, y));
			}
		}

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
		
		//Wall
		for (Point2D p : points){
			setStaticObject(ObjectLibrary::WOOD_WALL, p);
		}

		//Door
		Point2D doorPoint = points.at(Random::generator->getInt(0, points.size() - 1));
		setStaticObject(ObjectLibrary::WOOD_FLOOR, doorPoint);
		placeOperatable(ObjectLibrary::generateDoor(ObjectLibrary::WOOD_DOOR, ObjectLibrary::DOOR_LOOT), doorPoint);
	}
}
*/