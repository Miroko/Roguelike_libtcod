#pragma once
#include "Glyph.h"
#include "Point2D.h"

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

	virtual void onTick() = 0;
	
	void render();
	void update();

	Particle(Glyph glyph, Point2D location, int tickRate, int ageMax) : 
		glyph(glyph),
		location(location),
		currentAge(0), 
		currentTick(tickRate),
		ageMax(ageMax),
		tickRate(tickRate),
		dead(false){};
};

