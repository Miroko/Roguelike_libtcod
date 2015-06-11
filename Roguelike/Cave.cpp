#include "Cave.h"
#include "Direction.h"

Cave::Cave(int size, float corridorsPerTile, int corridorSize, float roomChance, int roomSize) : Area(size, STONE){
	int corridors = bounds.getSize() * corridorsPerTile;
	Point2D nextPoint = bounds.getCenterPoint();
	Point2D previousDirection;
	while (corridors > 0){
		//Next direction
		Point2D newDirection = Random::direction();

		int currentCorridorSize = corridorSize;
		while (currentCorridorSize > 0){
			//Place corridor			
			setStaticObject(STONE_FLOOR, nextPoint);
			
			//Place room
			if (Random::generator.getFloat(0.0, 1.0) <= roomChance){
				Rectangle roomBounds = Rectangle(Point2D(nextPoint.x - roomSize / 2, nextPoint.y - roomSize / 2),
					                             Point2D(nextPoint.x + roomSize / 2, nextPoint.y + roomSize / 2));
				Point2D roomPoint;
					for (int x = roomBounds.start.x; x <= roomBounds.end.x; x++){
						for (int y = roomBounds.start.y; y <= roomBounds.end.y; y++){
							roomPoint.x = x;
							roomPoint.y = y;
							if (bounds.contains(roomPoint)){
								setStaticObject(STONE_FLOOR, roomPoint);
							}
						}
					}
			}
			//Next point
			Point2D newNextPoint = nextPoint + newDirection;
			if (!bounds.contains(newNextPoint)){
				for (Point2D direction : DIRECTIONS){
					newNextPoint = nextPoint + direction;
					if (bounds.contains(newNextPoint)){
						break;
					}
				}
			}
			nextPoint = newNextPoint;

			--currentCorridorSize;
		}
		--corridors;
	}
}

