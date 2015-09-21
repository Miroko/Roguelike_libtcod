#include "VisualEffectPlayer.h"
#include "Engine.h"

void VisualEffectPlayer::playEffect(Point2D location, std::shared_ptr<VisualEffect> effect){
	if (!effect) return;
	if (!engine::playerHandler.getPlayerCreature()->ai->inFov(location)) return;

	std::shared_ptr<VisualEffect> clonedEffect = effect->clone();
	clonedEffect->setLocation(location);
	runningVisualEffects.push_back(clonedEffect);
}

void VisualEffectPlayer::update(){
	auto &effect = runningVisualEffects.begin();
	while (effect != runningVisualEffects.end()){
		effect->get()->update();
		if (effect->get()->particles.empty()) effect = runningVisualEffects.erase(effect);
		else ++effect;
	}
}

void VisualEffectPlayer::render(){
	for (auto &effect : runningVisualEffects){
		effect->render();
	}
}