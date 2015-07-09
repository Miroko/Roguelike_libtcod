#include "Anvil.h"
#include "Engine.h"
#include "EffectSparkles.h"

void Anvil::on(){
	OperatableObject::on();
	if (engine::playerHandler.getPlayerCreature()->ai->inFov(location)){
		engine::visualEffectHandler.playEffect(std::shared_ptr<ParticleEffect>(new EffectSparkles(location)));
	}
}
std::shared_ptr<OperatableObject> Anvil::copy(){
	return std::shared_ptr<OperatableObject>(new Anvil(*this));
}