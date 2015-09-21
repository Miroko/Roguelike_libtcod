#pragma once
#include "VisualEffect.h"
#include "Point2D.h"
#include <vector>
#include <memory>

class VisualEffectPlayer
{
public:
	std::vector<std::shared_ptr<VisualEffect>> runningVisualEffects;

	void playEffect(Point2D location, std::shared_ptr<VisualEffect> effect);

	void update();
	void render();

	VisualEffectPlayer(){};
};

