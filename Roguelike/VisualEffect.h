#pragma once
#include <memory>
#include <vector>
#include "Point2D.h"

class Particle;
class VisualEffect
{
public:
	std::vector<std::shared_ptr<Particle>> particles;

	void setLocation(Point2D location);
	void update();
	void render();

	std::shared_ptr<VisualEffect> clone();

	VisualEffect(std::vector<std::shared_ptr<Particle>> particles) :
		particles(particles){}
};

