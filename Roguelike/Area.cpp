#include "Area.h"
#include "Engine.h"

void Area::placeTile(Tile &tile, Point2D &location){
	if (!bounds.contains(location)) return;
	areaContainers[location.x][location.y].tile = &tile;
}

Tile* Area::getTile(Point2D &location){
	if (!bounds.contains(location)) return nullptr;
	return areaContainers[location.x][location.y].tile;
}

Point2D Area::getNearestTile(Point2D &location, Tile &tile){
	Point2D scanLocation = location;
	int offset = 0;
	while (
		scanLocation.x + offset <= bounds.end.x ||
		scanLocation.y + offset <= bounds.end.y ||
		scanLocation.x - offset >= bounds.start.x ||
		scanLocation.y - offset >= bounds.start.y){
		for (scanLocation.x = location.x - offset; scanLocation.x <= location.x + offset; scanLocation.x++){
			for (scanLocation.y = location.y - offset; scanLocation.y <= location.y + offset; scanLocation.y++){
				if (bounds.contains(scanLocation)){
					if (areaContainers[scanLocation.x][scanLocation.y].tile == &tile){
						return scanLocation;
					}
				}
			}
		}
		++offset;
	}
	throw "No tile found";
}

Point2D Area::getNearestTile(Point2D &location, Tile::Type type){
	Point2D scanLocation = location;
	int offset = 0;
	while (
		scanLocation.x + offset <= bounds.end.x ||
		scanLocation.y + offset <= bounds.end.y ||
		scanLocation.x - offset >= bounds.start.x ||
		scanLocation.y - offset >= bounds.start.y){
		for (scanLocation.x = location.x - offset; scanLocation.x <= location.x + offset; scanLocation.x++){
			for (scanLocation.y = location.y - offset; scanLocation.y <= location.y + offset; scanLocation.y++){
				if (bounds.contains(scanLocation)){
					if (areaContainers[scanLocation.x][scanLocation.y].tile->type == type){
						return scanLocation;
					}
				}
			}
		}
		++offset;
	}
	throw "No tile found";
}

std::vector<Point2D> Area::getOpenTiles(Rectangle &inRectangle){
	std::vector<Point2D> tileLocations;
	for (int x = inRectangle.start.x; x <= inRectangle.end.x; ++x){
		for (int y = inRectangle.start.y; y <= inRectangle.end.y; ++y){
			Point2D location = Point2D(x, y);
			if (bounds.contains(location)){
				auto &areaContainer = areaContainers[location.x][location.y];
				if (!areaContainer.tile->isOpen()) continue;
				if (areaContainer.operatableObject) continue;
				if (areaContainer.creature) continue;
				tileLocations.push_back(location);
			}
		}
	}
	return tileLocations;
}

void Area::placeTile(Tile &portal, Point2D &location, Tile &placeOnNearest){
	Point2D placementLocation = location;
	int offset = 0;
	while (
		placementLocation.x + offset <= bounds.end.x ||
		placementLocation.y + offset <= bounds.end.y ||
		placementLocation.x - offset >= bounds.start.x ||
		placementLocation.y - offset >= bounds.start.y){
		for (placementLocation.x = location.x - offset; placementLocation.x <= location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y <= location.y + offset; placementLocation.y++){
				if (bounds.contains(placementLocation)){
					if (areaContainers[placementLocation.x][placementLocation.y].tile == &placeOnNearest){
						placeTile(portal, placementLocation);
						return;
					}
				}
			}
		}
		++offset;
	}
}

void Area::placeCreature(std::shared_ptr<Creature> creature, Point2D &location){
	Point2D placementLocation = location;
	int offset = 0;
	while (
		placementLocation.x + offset <= bounds.end.x ||
		placementLocation.y + offset <= bounds.end.y ||
		placementLocation.x - offset >= bounds.start.x ||
		placementLocation.y - offset >= bounds.start.y){
		for (placementLocation.x = location.x - offset; placementLocation.x <= location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y <= location.y + offset; placementLocation.y++){
				if (isPassable(placementLocation, *creature)){
					creature->location = placementLocation;
					dynamicObjectsAlive.push_front(creature);
					areaContainers[placementLocation.x][placementLocation.y].creature = creature.get();
					return;
				}
			}
		}
		++offset;
	}
}

Creature& Area::getCreature(Point2D &location){
	return *areaContainers[location.x][location.y].creature;
}

std::vector<Creature*> Area::getCreatures(Rectangle &bounds){
	std::vector<Creature*> creaturesInBounds;
	for (int x = bounds.start.x; x <= bounds.end.x; ++x){
		for (int y = bounds.start.y; y <= bounds.end.y; ++y){
			if (areaContainers[x][y].creature){
				creaturesInBounds.push_back(areaContainers[x][y].creature);
			}
		}
	}
	return creaturesInBounds;
}

void Area::placeOperatable(std::shared_ptr<OperatableObject> operatable, Point2D &location){
	Point2D placementLocation = location;
	int offset = 0;
	while (
		placementLocation.x + offset <= bounds.end.x ||
		placementLocation.y + offset <= bounds.end.y ||
		placementLocation.x - offset >= bounds.start.x ||
		placementLocation.y - offset >= bounds.start.y){
		for (placementLocation.x = location.x - offset; placementLocation.x <= location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y <= location.y + offset; placementLocation.y++){
				if (isPassable(placementLocation, *operatable)){
					operatable->location = placementLocation;
					dynamicObjectsAlive.push_front(operatable);
					areaContainers[placementLocation.x][placementLocation.y].operatableObject = operatable.get();
					return;
				}
			}
		}
		++offset;
	}
}

OperatableObject& Area::getOperatable(Point2D &location){
	return *areaContainers[location.x][location.y].operatableObject;
}

std::vector<OperatableObject*> Area::getOperatables(Rectangle &bounds){
	std::vector<OperatableObject*> operatablesInBounds;
	for (int x = bounds.start.x; x <= bounds.end.x; ++x){
		for (int y = bounds.start.y; y <= bounds.end.y; ++y){
			if (areaContainers[x][y].operatableObject){
				operatablesInBounds.push_back(areaContainers[x][y].operatableObject);
			}
		}
	}
	return operatablesInBounds;
}

void Area::placeItem(std::shared_ptr<Item> item, Point2D &location){
	item->location = location;
	areaContainers[location.x][location.y].items.push_back(item);
}

void Area::removeItem(std::shared_ptr<Item> &item){
	auto itemsIterator = areaContainers[item->location.x][item->location.y].items.begin();
	while (itemsIterator != areaContainers[item->location.x][item->location.y].items.end()){
		if (*itemsIterator == item){
			areaContainers[item->location.x][item->location.y].items.erase(itemsIterator);
			break;
		}
		else ++itemsIterator;
	}
}
std::vector<std::shared_ptr<Item>>& Area::getItems(Point2D &location){
	return areaContainers[location.x][location.y].items;
}

double Area::getTransparency(Point2D &location){
	if (!bounds.contains(location)) return 0.0;
	return areaContainers[location.x][location.y].getTransparency();
}

bool Area::isPassable(Point2D &location, DynamicObject &dynamicObjectMoving){
	if (!bounds.contains(location)) return false;
	return areaContainers[location.x][location.y].isPassable(dynamicObjectMoving);
}

bool Area::moveDynamicObject(DynamicObject &dynamicObject, Point2D &location){
	if (!isPassable(location, dynamicObject)) return false;
	if (dynamicObject.isCreature()){
		areaContainers[location.x][location.y].creature = areaContainers[dynamicObject.location.x][dynamicObject.location.y].creature;
		areaContainers[dynamicObject.location.x][dynamicObject.location.y].creature = nullptr;
	}
	else if (dynamicObject.isOperatable()){
		areaContainers[location.x][location.y].operatableObject = areaContainers[dynamicObject.location.x][dynamicObject.location.y].operatableObject;
		areaContainers[dynamicObject.location.x][dynamicObject.location.y].operatableObject = nullptr;
	}
	dynamicObject.location = location;
	return true;
}

void Area::destroyDynamicObject(DynamicObject &dynamicObject){
	auto &dynamicObjectsAliveIterator = dynamicObjectsAlive.begin();
	while (dynamicObjectsAliveIterator != dynamicObjectsAlive.end()){
		if (dynamicObjectsAliveIterator->get() == &dynamicObject){
			dynamicObjectsDead.push_back(*dynamicObjectsAliveIterator); //add to dead
			break;
		}
		else ++dynamicObjectsAliveIterator;
	}
	if (dynamicObject.isCreature()){
		areaContainers[dynamicObject.location.x][dynamicObject.location.y].creature = nullptr;
	}
	else if (dynamicObject.isOperatable()){
		areaContainers[dynamicObject.location.x][dynamicObject.location.y].operatableObject = nullptr;
	}
}

void Area::cleanDeadObjects(){
	auto &dynamicObjectsDeadIterator = dynamicObjectsDead.begin();
	while (dynamicObjectsDeadIterator != dynamicObjectsDead.end()){
		dynamicObjectsAlive.remove(*dynamicObjectsDeadIterator); //remove dead from alive
		++dynamicObjectsDeadIterator;
	}
	dynamicObjectsDead.clear();
}

void Area::initAi(){
	for (auto &dynamicObject : dynamicObjectsAlive){
		if (dynamicObject->isCreature()){
			static_cast<Creature&>(*dynamicObject).initAi(*this);
		}
	}
}

void Area::update(){
	for (auto &dynamicObject : dynamicObjectsAlive){
		dynamicObject->update();
	}
	cleanDeadObjects();
}

void Area::render(){
	using engine::camera;
	double lightIntensity;
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (bounds.contains(Point2D(x, y))){
				if (engine::renderWithoutFov) lightIntensity = 1.0;
				else{
					lightIntensity = 
						engine::playerHandler.getPlayerCreature()->ai->fov.getLuminosity(
						engine::playerHandler.getPlayerCreature()->location,
						Point2D(x, y));
				}
				if (lightIntensity > 0.0){
					AreaContainer &areaContainer = areaContainers[x][y];
					areaContainer.tile->render(x - camera.location.x, y - camera.location.y, lightIntensity);
					if (areaContainer.operatableObject){
						areaContainer.operatableObject->render(x - camera.location.x, y - camera.location.y, lightIntensity);
					}
					if (areaContainer.creature){
						areaContainer.creature->render(x - camera.location.x, y - camera.location.y, lightIntensity);
					}
					else if (!areaContainer.items.empty()){
						areaContainer.getItemToRender(itemRenderNumberCurrent).render(x - camera.location.x, y - camera.location.y, lightIntensity);
					}
				}
			}
		}
	}
	++itemRenderRateCounter;
	if (itemRenderRateCounter == engine::renderItemsRate){
		++itemRenderNumberCurrent;
		if (itemRenderNumberCurrent == itemRenderNumberMax) itemRenderNumberCurrent = 0;
		itemRenderRateCounter = 0;
	}
}

void Area::generateBase(Rectangle bounds, Tile &tile){
	this->bounds = bounds;

	areaContainers.resize(bounds.getWidth() + 1);
	for (int x = 0; x < bounds.getWidth() + 1; x++){
		areaContainers[x].resize(bounds.getHeight() + 1, AreaContainer(tile));
	}
}

void Area::generateEdge(Tile &tile, int size, int randomTilesPerEdgeTile){
	for (Point2D &edgePoint : bounds.getEdgePoints()){
		Rectangle surrounding = Rectangle(edgePoint, edgePoint);
		surrounding.expand(size);
		for (int randomTile = randomTilesPerEdgeTile; randomTile > 0; --randomTile){
			Point2D &location = engine::random.point(surrounding);
			placeTile(tile, location);
		}
		placeTile(tile, edgePoint);
	}
}

