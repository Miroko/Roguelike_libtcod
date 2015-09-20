#include "CreatureEffect.h"
#include "Engine.h"
#include <algorithm>

CreatureEffect::CreatureEffect(std::string name, double modifier, double durationFromMax) :
	name(name),
	modifier(modifier),
	duration(std::max((int)(engine::effectDurationBase * durationFromMax), 1)){
}
