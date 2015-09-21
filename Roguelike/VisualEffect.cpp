#include "VisualEffect.h"
#include "Particle.h"

void VisualEffect::setLocation(Point2D location){
	for (auto &particle : particles){
		particle->location = location;
	}
}

void VisualEffect::update(){
	auto &particle = particles.begin();
	while (particle != particles.end()){
		particle->get()->update();
		if (particle->get()->dead) particle = particles.erase(particle);
		else ++particle;
	}
}

void VisualEffect::render(){
	for (auto &particle : particles){
		particle->render();
	}
}

std::shared_ptr<VisualEffect> VisualEffect::clone(){
	std::vector<std::shared_ptr<Particle>> clonedParticles;
	for (auto &particle : particles){
		clonedParticles.push_back(particle->clone());
	}
	return std::shared_ptr<VisualEffect>(new VisualEffect(clonedParticles));
}
