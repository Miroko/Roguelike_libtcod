#include "Village.h"
#include "Door.h"
#include "Creature.h"
#include "Human.h"
#include "Engine.h"

Village::Village() : Area(100, LAND){
	villageBounds = Rectangle(bounds);
	villageBounds.start.x += bounds.getWidth() / 4;
	villageBounds.start.y += bounds.getHeight() / 4;
	villageBounds.end.x -= bounds.getWidth() / 4;
	villageBounds.end.y -= bounds.getHeight() / 4;

	//Trees
	Random::generator.setDistribution(TCOD_DISTRIBUTION_GAUSSIAN_RANGE_INVERSE);
	int trees = bounds.getSize() / 20;
	for (int tree = trees; tree > 0; tree--){
		Point2D p = Random::point(bounds);
		if (!villageBounds.inside(p)){
			setStaticObject(TREE, p);
		}
	}
	Random::generator.setDistribution(TCOD_DISTRIBUTION_LINEAR);

	//House plots
	int plotSize = plotSize = Random::generator.getInt(3, 12);
	std::vector<Rectangle> plots;
	int largestPlot = 0;
	int offsetX = 0;
	int offsetY = 0;
	for (int x = villageBounds.start.x; x < villageBounds.end.x - largestPlot;){
		for (int y = villageBounds.start.y; y < villageBounds.end.y - largestPlot;){
			offsetX = Random::generator.getInt(2, 5);
			offsetY = Random::generator.getInt(2, 5);
			plotSize = Random::generator.getInt(3, 12); 
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
		std::vector<Point2D> points = plot.getPoints();

		//Floor
		for (int x = plot.start.x + 1; x < plot.end.x; x++){
			for (int y = plot.start.y + 1; y < plot.end.y; y++){
				setStaticObject(WOOD_FLOOR, Point2D(x, y));
			}
		}

		//Villager
		Rectangle villagerArea = Rectangle(Point2D(plot.start.x + 1, plot.start.y + 1),
			                               Point2D(plot.end.x, plot.end.y));
		int villagers = Random::generator.getInt(1, 3, 1);
		for (int villager = villagers; villager > 0; villager--){
			Point2D location = Random::point(villagerArea);
			std::shared_ptr<Human> human = Creature::newCreature(MAN, false);
			placeAliveObject(human, location);
		}

		//Wall
		for (Point2D p : points){
			setStaticObject(WOOD_WALL, p);
		}

		//Door
		Point2D doorPoint = points.at(Random::generator.getInt(0, points.size() - 1));
		setStaticObject(WOOD_FLOOR, doorPoint);
		placeDynamicObject(OperatableObject::newOperatable(WOOD_DOOR), doorPoint);
	}
}