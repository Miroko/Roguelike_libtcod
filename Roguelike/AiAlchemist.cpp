#include "AiAlchemist.h"
#include "Creature.h"
#include "Village.h"
#include "AlchemyTable.h"
#include "Engine.h"

void AiAlchemist::onTakeDamage(DynamicObject &attacker){
	if (attacker.type == Creature::CREATURE){
		combatModule.target = &attacker;
		combatModule.state = combatModule.PURSUE_TARGET;
		currentState = COMBAT;
	}
}
void AiAlchemist::onCreatureInFov(Creature &creature, int distance){
	if (combatModule.state != combatModule.JAMMED &&
		combatModule.state != combatModule.FLEE){
		if (&creature == combatModule.target){
			combatModule.state = combatModule.PURSUE_TARGET;
		}
	}
}
void AiAlchemist::onOperatableInFov(OperatableObject &operatable, int distance){
	if (currentState == USE_ALCHEMY_TABLE){
		if (operatable.type == OperatableObject::ALCHEMY_TABLE){
			if (alchemyTableUsing == nullptr){
				alchemyTableUsing = static_cast<AlchemyTable*>(&operatable);
				calculatePath(operatable.location, false);
			}
		}
	}
}
void AiAlchemist::nextToDestination(Point2D &location){

}
void AiAlchemist::onPathBlocked(Point2D &location){

}
void AiAlchemist::onPathEnd(Point2D &location){

}

void AiAlchemist::initAi(Creature &owner, Area &area){
	CreatureAi::initAi(owner, area);
	combatModule.init(*this);
	residentModule.init(*this);

	Village *village = static_cast<Village*>(&area);
	for (auto &house : village->houses){
		if (house.bounds.contains(owner.location)){
			residentModule.residence = &house;
			break;
		}
	}
	currentState = IN_HOUSE;
}

void AiAlchemist::update(){
	CreatureAi::update();
	if (currentState == COMBAT){
		combatModule.run();
	}
	else if (currentState == IN_HOUSE){
		residentModule.run();
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.50f){
			currentState = USE_ALCHEMY_TABLE;
		}
	}
	else if (currentState == USE_ALCHEMY_TABLE){
		if (alchemyTableUsing != nullptr){
			if (moveOnPath() == 1){
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.10f){
					alchemyTableUsing->on();
				}
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.20f){
					alchemyTableUsing = nullptr;
					currentState = IN_HOUSE;
				}
			}
		}
		else currentState = IN_HOUSE;
	}
}

std::shared_ptr<CreatureAi> AiAlchemist::copy(){
	return std::shared_ptr<CreatureAi>(new AiAlchemist(*this));
}

