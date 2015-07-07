#include "Area.h"
#include "Engine.h"

void Area::placeTile(Tile &tile, Point2D &location){
	if (bounds.contains(location)){
		tiles[location.x][location.y] = &tile;
	}
}

Tile *Area::getTile(Point2D &location){
	if (bounds.contains(location)){
		return tiles[location.x][location.y];
	}
	else return nullptr;
}

Point2D Area::getNearestTile(Point2D &location, Tile &tile){
	Point2D scanLocation = location;
	int offset = 0;
	while (
		scanLocation.x + offset != bounds.end.x &&
		scanLocation.y + offset != bounds.end.x &&
		scanLocation.x - offset != bounds.start.x &&
		scanLocation.y - offset != bounds.start.y){
		for (scanLocation.x = location.x - offset; scanLocation.x <= location.x + offset; scanLocation.x++){
			for (scanLocation.y = location.y - offset; scanLocation.y <= location.y + offset; scanLocation.y++){
				if (bounds.contains(scanLocation)){
					if (tiles[scanLocation.x][scanLocation.y] == &tile){
						return scanLocation;
					}
				}
			}
		}
		++offset;
	}
	return Point2D();
}

void Area::placeTile(Tile &portal, Point2D &location, Tile &placeOnNearest){
	Point2D placementLocation = location;
	int offset = 0;
	while (
		placementLocation.x + offset <= bounds.end.x &&
		placementLocation.y + offset <= bounds.end.x &&
		placementLocation.x - offset >= bounds.start.x &&
		placementLocation.y - offset >= bounds.start.y){
		for (placementLocation.x = location.x - offset; placementLocation.x <= location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y <= location.y + offset; placementLocation.y++){
				if (bounds.contains(placementLocation)){
					if (tiles[placementLocation.x][placementLocation.y] == &placeOnNearest){
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
		placementLocation.x + offset <= bounds.end.x &&
		placementLocation.y + offset <= bounds.end.x &&
		placementLocation.x - offset >= bounds.start.x &&
		placementLocation.y - offset >= bounds.start.y){
		for (placementLocation.x = location.x - offset; placementLocation.x <= location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y <= location.y + offset; placementLocation.y++){
				if (passable(placementLocation, *creature)){
					creature->location = placementLocation;
					creatures.push_back(creature);
					return;
				}
			}
		}
		++offset;
	}
}

std::vector<std::shared_ptr<Creature>*> Area::getCreatures(Point2D &location){
	std::vector<std::shared_ptr<Creature>*> creaturesAtLocation;
	for (auto &creature : creatures){
		if (creature->location == location){
			creaturesAtLocation.push_back(&creature);
		}
	}
	return creaturesAtLocation;
}

std::vector<std::shared_ptr<Creature>*> Area::getCreatures(Rectangle &bounds){
	std::vector<std::shared_ptr<Creature>*> creaturesInBounds;
	for (auto &creature : creatures){
		if (bounds.contains(creature->location)){
			creaturesInBounds.push_back(&creature);
		}
	}
	return creaturesInBounds;
}

void Area::placeOperatable(std::shared_ptr<OperatableObject> operatable, Point2D &location){
	Point2D placementLocation = location;
	int offset = 0;
	while (
		placementLocation.x + offset <= bounds.end.x &&
		placementLocation.y + offset <= bounds.end.x &&
		placementLocation.x - offset >= bounds.start.x &&
		placementLocation.y - offset >= bounds.start.y){
		for (placementLocation.x = location.x - offset; placementLocation.x <= location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y <= location.y + offset; placementLocation.y++){
				if (passable(placementLocation, *operatable)){
					operatable->location = placementLocation;
					operatableObjects.push_back(operatable);
					return;
				}
			}
		}
		++offset;
	}
}

std::vector<std::shared_ptr<OperatableObject>*> Area::getOperatables(Point2D &location){
	std::vector<std::shared_ptr<OperatableObject>*> operatablesInLocation;
	for (auto &operatable : operatableObjects){
		if (operatable->location == location){
			operatablesInLocation.push_back(&operatable);
		}
	}
	return operatablesInLocation;
}

std::vector<std::shared_ptr<OperatableObject>*> Area::getOperatables(Rectangle &bounds){
	std::vector<std::shared_ptr<OperatableObject>*> operatablesInBounds;
	for (auto &operatable : operatableObjects){
		if (bounds.contains(operatable->location)){
			operatablesInBounds.push_back(&operatable);
		}
	}
	return operatablesInBounds;
}

void Area::placeItem(std::shared_ptr<Item> item, Point2D &toLocation){
	item->location = toLocation;
	items.push_back(item);
}

void Area::removeItem(std::shared_ptr<Item> &item){
	auto currentItem = items.begin();
	while (currentItem != items.end()){
		if (*currentItem == item){
			items.erase(currentItem);
			break;
		}
		else ++currentItem;
	}
}

std::vector<std::shared_ptr<Item>*> Area::getItemsAt(Point2D &location){
	std::vector<std::shared_ptr<Item>*> itemsAtLocation;
	for (auto &item : items){
		if (item->location == location){
			itemsAtLocation.push_back(&item);
		}
	}
	return itemsAtLocation;
}

bool Area::passable(Point2D &location, DynamicObject &dynamicObjectMoving){
	if (bounds.contains(location)){
		if (tiles[location.x][location.y]->type == GameObject::WALL) return false;
		for (auto &o : creatures){
			if (o->location == location){
				if (!o->passable(dynamicObjectMoving)){
					return false;
				}
			}
		}
		for (auto &o : operatableObjects){
			if (o->location == location){
				if (!o->passable(dynamicObjectMoving)){
					return false;
				}
			}
		}
		return true;
	}
	else return false;
}

void Area::cleanDeadDynamicObjects(){
	if (cleaningRequired){
		auto &creature = creatures.begin();
		while (creature != creatures.end()){
			if (creature->get()->isDead){
				creature = creatures.erase(creature);
			}
			else ++creature;
		}
		auto &operatable = operatableObjects.begin();
		while (operatable != operatableObjects.end()){
			if (operatable->get()->isDead){
				operatable = operatableObjects.erase(operatable);
			}
			else ++operatable;
		}
		cleaningRequired = false;
	}
}

Rectangle &Area::getBounds(){
	return bounds;
}

void Area::requireClean(){
	cleaningRequired = true;
}

void Area::generateBase(Rectangle bounds, Tile &tile){
	this->bounds = bounds;

	tiles.resize(bounds.getWidth() + 1);
	for (int x = 0; x < bounds.getWidth() + 1; x++){
		tiles[x].resize(bounds.getHeight() + 1, &tile);
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


void Area::initAi(){
	for (auto &creature : creatures){
		creature->initAi(*this);
	}
}

void Area::update(){
	for (auto &creature : creatures){
		if (!creature->isDead){
			creature->update();
		}
	}
	for (auto &operatable : operatableObjects){
		if (!operatable->isDead){
			operatable->update();
		}
	}
}

void Area::render(){
	using engine::camera;
	using engine::playerHandler;
	//Static objects
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (bounds.contains(Point2D(x, y))){
				if (playerHandler.getPlayerCreature()->ai->inFov(Point2D(x, y)) || SEE_THROUGH){
					tiles[x][y]->render(x - camera.location.x, y - camera.location.y);
				}
			}
		}
	}
	//Item
	for (auto &item : items){
		int renderX = item->location.x - camera.location.x;
		int renderY = item->location.y - camera.location.y;
		if (playerHandler.getPlayerCreature()->ai->inFov(item->location) || SEE_THROUGH){
			item->render(renderX, renderY);
		}
	}
	//Operatables
	for (auto &operatable : operatableObjects){
		int renderX = operatable->location.x - camera.location.x;
		int renderY = operatable->location.y - camera.location.y;
		if (playerHandler.getPlayerCreature()->ai->inFov(operatable->location) || SEE_THROUGH){
			operatable->render(renderX, renderY);
		}
	}
	//Creatures
	for (auto &creature : creatures){
		int renderX = creature->location.x - camera.location.x;
		int renderY = creature->location.y - camera.location.y;
		if (playerHandler.getPlayerCreature()->ai->inFov(creature->location) || SEE_THROUGH){
			creature->render(renderX, renderY);
		}
	}
}
