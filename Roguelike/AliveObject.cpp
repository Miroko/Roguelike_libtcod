#include "AliveObject.h"
#include "Engine.h"

void AliveObject::createFovMap(){
	fovMap = std::shared_ptr<TCODMap>(new TCODMap(Engine::area.bounds.getWidth(), Engine::area.bounds.getHeight()));
	int startX = 0;
	int startY = 0;
	int endX = fovMap->getWidth();
	int endY = fovMap->getHeight();
	for (int x = startX; x < endX; x++){
		for (int y = startY; y < endY; y++){
			fovMap->setProperties(x, y,
				Engine::area.staticObjects[x][y]->transparent, Engine::area.staticObjects[x][y]->passable());
		}
	}
}

void AliveObject::calculateFov(){
	//Update fov map
	for (auto &o : Engine::area.dynamicObjects){
		if (o->isDead) fovMap->setProperties(o->location.x, o->location.y,
			Engine::area.staticObjects[o->location.x][o->location.y]->transparent,
			Engine::area.staticObjects[o->location.x][o->location.y]->passable());
		else{
			fovMap->setProperties(o->location.x, o->location.y, o->transparent, o->passable());
		}
	}
	//Compute
	fovMap->computeFov(location.x, location.y, FOV_RADIUS_MAX, true, FOV_RESTRICTIVE);
}

bool AliveObject::inFov(int x, int y){
	return fovMap->isInFov(x, y);
}

float AliveObject::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	AliveObject *thisObject = static_cast<AliveObject*>(userData);
	if (Engine::area.staticObjects[xTo][yTo]->passable() == false) return 0;

	for (auto &o : Engine::area.dynamicObjects){
		if (o->isDead) continue;

		if (o->location.x == xTo && o->location.y == yTo){
			if (!o->passable()){
				if (o.get() == thisObject->target.get()){
					// Computing path to target
					return 1;
				}
				else{
					return 0;
				}
			}
		}
	}

	return 1;
}

void AliveObject::createPathMap(){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		Engine::area.bounds.getWidth(),
		Engine::area.bounds.getHeight(),
		new PathCostCallback(),
		this));
}

void AliveObject::calculatePath(int toX, int toY){
	pathMap->compute(location.x, location.y, toX, toY);
}

void AliveObject::setTarget(std::shared_ptr<DynamicObject> target){
	this->target = target;
}

//Returns true if target in next spot else false
bool AliveObject::moveOnPath(){
	if (!pathMap->isEmpty()){
		int x, y;
		if (pathMap->walk(&x, &y, false) == true){
			if (target->location == Point2D(x, y)){
				// Target in next point
				return true;
			}
			else{
				// Move
				location.x = x;
				location.y = y;
			}
		}
		else{
			// Stuck
		}
	}
	else{
		//Lost track
	}
	return false;
}

bool AliveObject::targetInFov(){
	if (inFov(target->location.x, target->location.y)) return true;
	else return false;
}

void AliveObject::calculatePathToTarget(){
	calculatePath(target->location.x, target->location.y);
}

void AliveObject::damage(std::shared_ptr<DynamicObject> &target){
	target->onTakeDamage(weapon->damage);
}

void AliveObject::attackMelee(std::shared_ptr<DynamicObject> &target){
	Engine::GUI.log.addToMessage(name + " attacks " + target->name + " with " + weapon->name + ". ");
	damage(target);
}

void AliveObject::attackRanged(std::shared_ptr<DynamicObject> &target){
	Engine::GUI.log.addToMessage(name + " shoots " + target->name + " with " + weapon->name + ". ");
	damage(target);
}

void AliveObject::onTakeDamage(int amount){
	int amountAfterDefence = amount;
	int bodyPart = Random::generator.getInt(0, 3, 2);
	switch (bodyPart){
	case 3: if (armorHead != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorHead->defence, armorHead->defence); Engine::GUI.log.addToMessage("Head is hit. "); break;
	case 2: if (armorBody != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorBody->defence, armorBody->defence); Engine::GUI.log.addToMessage("Body is hit. "); break;
	case 1: if (armorHand != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorHand->defence, armorHand->defence); Engine::GUI.log.addToMessage("Arm is hit. "); break;
	case 0: if (armorLeg != nullptr) amountAfterDefence -= Random::generator.getInt(0, armorLeg->defence, armorLeg->defence); Engine::GUI.log.addToMessage("Leg is hit. "); break;
	default: break;
	}
	if (amountAfterDefence < 0) amountAfterDefence = 0;
	DynamicObject::onTakeDamage(amountAfterDefence);
}

void AliveObject::update(){
	//Effects
	auto &effect = effects.items.begin();
	while (effect != effects.items.end()){
		if (effect->get()->duration <= 0){
			effect = effects.items.erase(effect);
		}
		else{
			effect->get()->duration--;
			effect->get()->update(*this);
			++effect;
		}
	}
	//AI
	calculateFov();
	if (target != nullptr){
		if (!target->isDead){
			if (!targetInFov()){ //Can't see target
				moveOnPath(); //Move using path to last seen position
				return;
			}
			else calculatePathToTarget(); //Target in fov, calculate new path to it

			if (weapon != nullptr){
				switch (weapon->type) {
				case Weapon::WEAPON_MELEE:
					if (moveOnPath()) attackMelee(target);
					break;
				case Weapon::WEAPON_RANGED:{
					int distance = location.distance(target->location);
					if (distance <= RANGED_SHOOT_DISTANCE_MAX){
						attackRanged(target);
					}
					else moveOnPath();
			    	}
					break;
				default: break;
				}
			}
		}
	}
}

void AliveObject::equip(std::shared_ptr<Item> equipment){
	switch (equipment->type){
	case Item::WEAPON_MELEE: weapon = std::static_pointer_cast<Weapon>(equipment); break;
	case Item::WEAPON_RANGED: weapon = std::static_pointer_cast<Weapon>(equipment); break;
	case Item::ARMOR_HEAD: armorHead = std::static_pointer_cast<Armor>(equipment); break;
	case Item::ARMOR_BODY: armorBody = std::static_pointer_cast<Armor>(equipment); break;
	case Item::ARMOR_HAND: armorHand = std::static_pointer_cast<Armor>(equipment); break;
	case Item::ARMOR_LEG: armorLeg = std::static_pointer_cast<Armor>(equipment); break;
	default: break;
	}
}

void AliveObject::consume(std::shared_ptr<Item> consumable){
	Consumable *c = static_cast<Consumable*>(consumable.get());
	for (auto &effect : c->effects){
		switch (effect->type){
		case AliveObjectEffect::HEAL: addEffect(AliveObjectEffect::newEffect(std::static_pointer_cast<Heal>(effect))); break;
		default: break;
		}
	}
}

void AliveObject::addEffect(std::shared_ptr<AliveObjectEffect> effect){
	effects.add(effect);
}