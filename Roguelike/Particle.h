#pragma once
#include "Glyph.h"
#include "Point2D.h"
#include <memory>

class Particle
{
public:
	bool dead;
	Glyph glyph;
	int currentAge;
	int ageMax;
	int tickRate;
	int currentTick;
	Point2D location;

	void render();
	void update();

	virtual void onTick() = 0;
	virtual std::shared_ptr<Particle> clone() = 0;

	Particle(Glyph glyph, int tickRate, int ageMax) : 
		glyph(glyph),
		location(Point2D()),
		currentAge(0), 
		currentTick(tickRate),
		ageMax(ageMax),
		tickRate(tickRate),
		dead(false){};
};

