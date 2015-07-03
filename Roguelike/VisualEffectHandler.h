#pragma once
#include "VisualEffect.h"
#include <vector>
#include <memory>

class VisualEffectHandler
{
public:
	std::vector<VisualEffect> effects;

	void playEffect(Point2D &location, Point2D &direction, const VisualEffect &effectTemplate);

	void render();

	VisualEffectHandler(){};
};

