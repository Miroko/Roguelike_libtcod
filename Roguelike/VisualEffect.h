#pragma once
#include "libtcod.hpp"
#include "Line.h"
#include <memory>

class VisualEffect
{
public:
	static const VisualEffect BLOOD_SPLATTER;

	Line path;
	int pathIndex;
	TCODColor color;
	int duration;
	int currentDuration;

	void update();
	void render();

	VisualEffect(const TCODColor &color, Point2D start, Point2D direction, int duration);

	VisualEffect();
};

