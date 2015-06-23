#include "VisualEffect.h"
#include "Direction.h"
#include "Engine.h"
#include "libtcod.hpp"
#include <cmath>

const VisualEffect VisualEffect::BLOOD_SPLATTER = VisualEffect(TCODColor::darkRed, Point2D(0,0), Point2D(0,0), 12);

VisualEffect::VisualEffect(const TCODColor &color, Point2D start, Point2D direction, int duration) :
  color(color), duration(duration), currentDuration(duration), path((Line(start, start + direction))), pathIndex(0){

};

void VisualEffect::update(){
	float time = 1.0 - (float)currentDuration / (float)duration;
	pathIndex = round((path.points.size() - 1) * time);
	currentDuration--;
}

void VisualEffect::render(){
	float time = (float)currentDuration / (float)duration;
	TCODConsole::root->setCharBackground(path.points.at(pathIndex)->x - Engine::camera.location.x, path.points.at(pathIndex)->y - Engine::camera.location.y,
		                                 color, TCOD_BKGND_ADDALPHA(time));
}