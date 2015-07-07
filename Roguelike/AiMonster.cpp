#include "AiMonster.h"
#include "Creature.h"
#include "Engine.h"

void AiMonster::onTakeDamage(DynamicObject &attacker){

}
void AiMonster::onCreatureInFov(Creature &creature, int distance){
	if (&creature == engine::playerHandler.getPlayerCreature().get()){
		combat.target = &creature;
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
	combat.init(*this);
}
void AiMonster::update(){
	CreatureAi::update();
	combat.run();
}

std::shared_ptr<CreatureAi> AiMonster::copy(){
	return std::shared_ptr<CreatureAi>(new AiMonster(*this));
}