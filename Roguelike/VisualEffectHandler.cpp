#include "VisualEffectHandler.h"
#include "EffectBloodSplatter.h"

void VisualEffectHandler::playEffect(std::shared_ptr<ParticleEffect> effect){
	runningEffects.push_back(effect);
}

void VisualEffectHandler::render(){
	auto &effect = runningEffects.begin();
	while (effect != runningEffects.end()){
		effect->get()->render();
		effect->get()->update();
		if (effect->get()->particles.empty()) effect = runningEffects.erase(effect);
		else ++effect;
	}
}