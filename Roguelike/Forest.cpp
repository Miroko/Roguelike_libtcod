#include "Forest.h"

Forest::Forest(int size, int tree, int rock) : Area(size, LAND){
	int trees = bounds.getSize() / tree;
	for (int tree = trees; tree > 0; tree--){
		Point2D p = Point2D(Random::generator.getInt(0, bounds.getWidth() - 1), Random::generator.getInt(0, bounds.getHeight() - 1));
		setStaticObject(TREE, p);
	}

	int rocks = bounds.getSize() / rock;
	for (int rock = rocks; rock > 0; rock--){
		Point2D p = Point2D(Random::generator.getInt(0, bounds.getWidth() - 1), Random::generator.getInt(0, bounds.getHeight() - 1));
		setStaticObject(STONE, p);
	}
}