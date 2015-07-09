#pragma once
#include "ParticleEffect.h"
#include "EffectBloodSplatter.h"
#include <vector>
#include <memory>

class VisualEffectHandler
{
public:
	std::vector<std::shared_ptr<ParticleEffect>> runningEffects;

	void playEffect(std::shared_ptr<ParticleEffect> effects);

	void render();

	VisualEffectHandler(){};
};

