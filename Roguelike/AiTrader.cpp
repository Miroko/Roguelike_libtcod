#include "AiTrader.h"
#include "Creature.h"
#include "Engine.h"
#include "Rectangle.h"
#include "Village.h"

void AiTrader::onTakeDamage(DynamicObject &attacker){
	combatModule.target = dynamic_cast<Creature*>(&attacker);
	if (combatModule.target != nullptr){
		currentState = COMBAT;
	}
}
void AiTrader::onCreatureInFov(Creature &creature, int distance){

}
void AiTrader::onOperatableInFov(OperatableObject &operatable, int distance){

}
void AiTrader::nextToDestination(Point2D &location){

}
void AiTrader::onPathBlocked(Point2D &location){

}
void AiTrader::onPathEnd(Point2D &location){

}

void AiTrader::initAi(Creature &owner, Area &area){
	CreatureAi::initAi(owner, area);
	combatModule.init(*this);
	currentState = IN_HOUSE;

	Village *village = static_cast<Village*>(&area);
	for (auto &house : village->houses){
		if (house.bounds.contains(owner.location)){
			houseIn = &house;
			break;
		}
	}
}

void AiTrader::update(){
	CreatureAi::update();
	if (currentState == COMBAT){
		combatModule.run();
	}
	else if (currentState == IN_HOUSE){
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.10f){
			Point2D newLocation = owner->location + engine::random.direction();
			if (currentState == IN_HOUSE && houseIn != nullptr){
				Rectangle houseInside = houseIn->bounds;
				houseInside.shrink(1);
				if (houseInside.contains(newLocation)){
					owner->move(newLocation);
				}
			}
			else{
				owner->move(newLocation);
			}
		}
	}
}
std::shared_ptr<CreatureAi> AiTrader::copy(){
	return std::shared_ptr<CreatureAi>(new AiTrader(*this));
}