#include "VisualEffectHandler.h"

void VisualEffectHandler::playEffect(Point2D &location, Point2D &direction, const VisualEffect &effectTemplate){
	effects.push_back(VisualEffect(effectTemplate.color, location, direction, effectTemplate.duration));
}

void VisualEffectHandler::render(){
	auto &effect = effects.begin();
	while (effect != effects.end()){
		effect->render();
		effect->update();
		if (effect->currentDuration == 0){
			effect = effects.erase(effect);
		}
		else{
			++effect;
		}
	}
}