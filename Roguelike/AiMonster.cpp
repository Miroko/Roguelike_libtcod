#include "AiMonster.h"
#include "Creature.h"
#include "Engine.h"

void AiMonster::onTakeDamage(DynamicObject &attacker){

}
void AiMonster::onCreatureInFov(Creature &creature, int distance){
	if (&creature == engine::playerHandler.getPlayerCreature().get()){
		target = &creature;
		setTargetLocation(target->location);
	}
}
void AiMonster::onOperatableInFov(OperatableObject &operatable,int distance){

}
void AiMonster::onDestination(Point2D &location){
	if (target != nullptr){
		if (target->location == location){
			owner->attack(*target);
		}
	}
}
void AiMonster::onPathBlocked(Point2D &location){

}
void AiMonster::onPathEnd(Point2D &location){

}

void AiMonster::initAi(Creature &owner){
	CreatureAi::initAi(owner);
}

void AiMonster::update(){
	CreatureAi::update();
}