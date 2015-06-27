#include "Forest.h"
#include "ObjectLibrary.h"

Forest::Forest(int size, int tree, int rock) : Area(size, ObjectLibrary::FOREST_LAND){
	int trees = bounds.getSize() / tree;
	for (int tree = trees; tree > 0; tree--){
		Point2D p = Point2D(Random::generator.getInt(0, bounds.getWidth() - 1), Random::generator.getInt(0, bounds.getHeight() - 1));
		setStaticObject(ObjectLibrary::FOREST_TREE, p);
	}

	int rocks = bounds.getSize() / rock;
	for (int rock = rocks; rock > 0; rock--){
		Point2D p = Point2D(Random::generator.getInt(0, bounds.getWidth() - 1), Random::generator.getInt(0, bounds.getHeight() - 1));
		setStaticObject(ObjectLibrary::STONE_WALL, p);
	}
}