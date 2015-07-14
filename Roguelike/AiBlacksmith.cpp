#include "AiBlacksmith.h"
#include "Creature.h"
#include "Village.h"
#include "Forge.h"
#include "Anvil.h"
#include "Engine.h"

void AiBlacksmith::onTakeDamage(DynamicObject &attacker){
	if (attacker.type == Creature::CREATURE){
		combatModule.target = &attacker;
		currentState = COMBAT;
	}
}
void AiBlacksmith::onCreatureInFov(Creature &creature, int distance){

}
void AiBlacksmith::onOperatableInFov(OperatableObject &operatable, int distance){
	if (currentState == USE_FORGE){
		if (operatable.type == OperatableObject::FORGE){
			forgeUsing = static_cast<Forge*>(&operatable);
			calculatePath(operatable.location, true);
		}
	}
	else if (currentState == USE_ANVIL){
		if (operatable.type == OperatableObject::ANVIL){
			anvilUsing = static_cast<Anvil*>(&operatable);
			calculatePath(operatable.location, true);
		}
	}
}
void AiBlacksmith::nextToDestination(Point2D &location){

}
void AiBlacksmith::onPathBlocked(Point2D &location){

}
void AiBlacksmith::onPathEnd(Point2D &location){

}

void AiBlacksmith::initAi(Creature &owner, Area &area){
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

void AiBlacksmith::update(){
	CreatureAi::update();
	if (currentState == COMBAT){
		combatModule.run();
	}
	else if (currentState == IN_HOUSE){
		residentModule.run();
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.20f){
			currentState = USE_FORGE;
		}
		else if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.20f){
			currentState = USE_ANVIL;
		}
	}
	else if (currentState == USE_FORGE){
		if (forgeUsing != nullptr){
			if (moveOnPath() == 1){
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.10f){
					forgeUsing->on();
				}
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.05f){
					forgeUsing = nullptr;
					currentState = IN_HOUSE;
				}
			}
		}
		else currentState = IN_HOUSE;
	}
	else if (currentState == USE_ANVIL){
		if (anvilUsing != nullptr){
			if (moveOnPath() == 1){
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.30f){
					anvilUsing->on();
				}
				if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.05f){
					anvilUsing = nullptr;
					currentState = IN_HOUSE;
				}
			}
		}
		else currentState = IN_HOUSE;
	}
}

std::shared_ptr<CreatureAi> AiBlacksmith::copy(){
	return std::shared_ptr<CreatureAi>(new AiBlacksmith(*this));
}

