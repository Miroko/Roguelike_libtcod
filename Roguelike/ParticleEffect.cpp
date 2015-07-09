#include "ParticleEffect.h"

void ParticleEffect::update(){
	auto &particle = particles.begin();
	while (particle != particles.end()){
		particle->get()->update();
		if (particle->get()->dead) particle = particles.erase(particle);
		else ++particle;
	}
}

void ParticleEffect::render(){
	for (auto &particle : particles){
		particle->render();
	}
}