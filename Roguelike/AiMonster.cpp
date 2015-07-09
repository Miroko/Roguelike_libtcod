#include "AiMonster.h"
#include "Creature.h"
#include "Engine.h"

void AiMonster::onTakeDamage(DynamicObject &attacker){

}
void AiMonster::onCreatureInFov(Creature &creature, int distance){
	if (&creature == engine::playerHandler.getPlayerCreature().get()){
		combatModule.target = &creature;
	}
}
void AiMonster::onOperatableInFov(OperatableObject &operatable,int distance){

}
void AiMonster::nextToDestination(Point2D &location){

}
void AiMonster::onPathBlocked(Point2D &location){

}
void AiMonster::onPathEnd(Point2D &location){

}
void AiMonster::initAi(Creature &owner, Area &area){
	CreatureAi::initAi(owner, area);
	combatModule.init(*this);
}
void AiMonster::update(){
	CreatureAi::update();
	combatModule.run();
}

std::shared_ptr<CreatureAi> AiMonster::copy(){
	return std::shared_ptr<CreatureAi>(new AiMonster(*this));
}