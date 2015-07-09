#pragma once
#include "Particle.h"
#include <vector>
#include <memory>

class ParticleEffect
{
public:
	std::vector<std::shared_ptr<Particle>> particles;

	void update();
	void render();

	ParticleEffect(std::vector<std::shared_ptr<Particle>> particles) : particles(particles){};
};

