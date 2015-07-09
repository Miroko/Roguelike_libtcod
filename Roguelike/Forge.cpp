#include "Forge.h"
#include "Engine.h"
#include "EffectSmoke.h"

void Forge::on(){
	OperatableObject::on();
	if (engine::playerHandler.getPlayerCreature()->ai->inFov(location)){
		engine::visualEffectHandler.playEffect(std::shared_ptr<ParticleEffect>(new EffectSmoke(location)));
	}
}

std::shared_ptr<OperatableObject> Forge::copy(){
	return std::shared_ptr<OperatableObject>(new Forge(*this));
}