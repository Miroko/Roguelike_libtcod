#include "AlchemyTable.h"
#include "Engine.h"
#include "EffectAlchemySmoke.h"

void AlchemyTable::on(){
	OperatableObject::on();
	if (engine::playerHandler.getPlayerCreature()->ai->inFov(location)){
		engine::visualEffectHandler.playEffect(std::shared_ptr<ParticleEffect>(new EffectAlchemySmoke(location)));
	}
}
std::shared_ptr<OperatableObject> AlchemyTable::copy(){
	return std::shared_ptr<OperatableObject>(new AlchemyTable(*this));
}