#include "Particle.h"
#include "Engine.h"

void Particle::render(){
	float density = (float)currentAge / (float)ageMax;
	TCODConsole::root->setCharBackground(
		location.x - engine::camera.location.x,
		location.y - engine::camera.location.y,
		glyph.bgColor, TCOD_BKGND_ADDALPHA(1.0f - density));
}

void Particle::update(){
	if (currentTick == 0){
		onTick();
		currentTick = tickRate;
	}
	if (currentAge == ageMax){
		dead = true;
	}	
	++currentAge;
	--currentTick;
}

