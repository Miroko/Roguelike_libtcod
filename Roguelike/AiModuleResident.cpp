#include "AiModuleResident.h"
#include "AreaDen.h"
#include "Engine.h"
#include "Bed.h"

void AiModuleResident::wanderInsideResidence(AreaDen &residence){
	if (&residence != nullptr){
		if (engine::random.chance(0.30)){
			Point2D newLocation = owner->owner->location + engine::random.direction();
			Rectangle houseInside = residence.bounds;
			houseInside.shrink(1);
			if (houseInside.contains(newLocation)){
				owner->owner->move(newLocation);
			}
		}
	}
}
void AiModuleResident::sleep(Bed &bed){
	if (&bed == nullptr ||
		!residence->bounds.contains(bed.location) ||
		bed.isInUse()){
		currentState = WANDER;
	}
	else{
		owner->calculatePath(bed.location);
		if (owner->moveOnPath() == 0){
			bed.operate(*owner->owner);
			currentState = SLEEPING;
		}
	}
}
void AiModuleResident::run(){
	if (currentState == WANDER){
		wanderInsideResidence(*residence);
		if (engine::random.chance(0.01)){
			currentState = GO_SLEEP;
		}
	}
	else if (currentState == GO_SLEEP){
		sleep(*bed);
	}
	else if (currentState == SLEEPING){
		if (engine::random.chance(0.05)){
			bed->operate(*owner->owner);
			currentState = WANDER;
		}
	}
	else throw "No state selected";
}
