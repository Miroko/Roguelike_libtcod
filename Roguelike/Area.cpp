#include "Area.h"

Area::Area(int size, StaticObject &base) :
bounds(Rectangle(Point2D(0, 0), Point2D(size, size)))
{
	staticObjects.resize(bounds.getWidth());
	for (int x = 0; x < bounds.getWidth(); x++){
		staticObjects[x].resize(bounds.getHeight(), &base);
	}	
}

void Area::setStaticObject(StaticObject &staticObject, Point2D &location){
	staticObjects[(int)location.x][(int)location.y] = &staticObject;
}

void Area::placePortal(std::shared_ptr<Portal> portal, Point2D &location){
	Point2D placementLocation = location;
	int offset = 0;
	while (true){
		for (placementLocation.x = location.x - offset; placementLocation.x < location.x + offset; placementLocation.x++){
			for (placementLocation.y = location.y - offset; placementLocation.y < location.y + offset; placementLocation.y++){
				if (bounds.inside(placementLocation)){
					if (!staticObjects[placementLocation.x][placementLocation.y]->raised){
						portal->location = placementLocation;
						portals.push_back(portal);
						return;
					}
				}
			}
		}
		++offset;
	}
}

void Area::placeCreature(std::shared_ptr<Creature> creature, Point2D &location){
	if (moveCreature(*creature, location)){
		creatures.push_back(creature);
	}
	else {
		//Increase placement area until placed on open spot
		Point2D alternativeLocation = location;
		int offset = 1;
		while (true){ //Every object must be placed somewhere
			for (alternativeLocation.x = location.x - offset; alternativeLocation.x < location.x + offset; alternativeLocation.x++){
				for (alternativeLocation.y = location.y - offset; alternativeLocation.y < location.y + offset; alternativeLocation.y++){
					if (moveCreature(*creature, alternativeLocation)){
						creatures.push_back(creature);
						goto INIT_AI;
					}
				}
			}
			++offset;
		}
	}
	INIT_AI:
	creature->ai.createFovMap(*this);
	creature->ai.calculateFov(*this, *creature);
	creature->ai.createPathMap(*this, *creature);
}

bool Area::moveCreature(Creature &creature, Point2D &location){
	if (bounds.inside(location)){
		if (staticObjects[location.x][location.y]->raised) return false;
		for (auto &o : creatures){
			if (o->location == location){
				if (!o->passable(creature)){
					return false;
				}
			}
		}
		for (auto &o : operatableObjects){
			if (o->location == location){
				if (!o->passable(creature)){
					return false;
				}
			}
		}
		creature.location = location;
		return true;
	}
	return false;
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
	if (moveOperatable(operatable, location)){
		operatableObjects.push_back(operatable);
		return;
	}
	else {
		//Increase placement area until placed on open spot
		Point2D alternativeLocation = location;
		int offset = 1;
		while (true){ //Every object must be placed somewhere
			for (alternativeLocation.x = location.x - offset; alternativeLocation.x < location.x + offset; alternativeLocation.x++){
				for (alternativeLocation.y = location.y - offset; alternativeLocation.y < location.y + offset; alternativeLocation.y++){
					if (moveOperatable(operatable, alternativeLocation)){
						operatableObjects.push_back(operatable);
						return;
					}
				}
			}
			++offset;
		}
	}
}

bool Area::moveOperatable(std::shared_ptr<OperatableObject> &operatable, Point2D &location){
	if (bounds.inside(location)){
		if (staticObjects[location.x][location.y]->raised) return false;
		for (auto &o : operatableObjects){
			if (o->location == location){
				if (!o->passable(*operatable)){
					return false;
				}
			}
		}
		for (auto &o : creatures){
			if (o->location == location){
				if (!o->passable(*operatable)){
					return false;
				}
			}
		}
		operatable->location = location;
		return true;
	}
	return false;
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

void Area::killDynamicObject(DynamicObject &dynamicObject){
	dynamicObject.isDead = true;
	requireClean = true;
}

void Area::cleanDeadDynamicObjects(){
	if (requireClean){
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
		requireClean = false;
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
