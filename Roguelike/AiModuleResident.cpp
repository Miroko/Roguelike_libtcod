#include "AiModuleResident.h"
#include "AreaHouse.h"
#include "Engine.h"
#include "Bed.h"

void AiModuleResident::wanderInsideResidence(AreaHouse &residence){
	if (&residence != nullptr){
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.30f){
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
	if (&bed != nullptr &&
		residence->bounds.contains(bed.location) &&
		!bed.isInUse()){
		owner->calculatePath(bed.location);
		if (owner->moveOnPath() == 0){
			bed.operate(*owner->owner);
			currentState = SLEEPING;
		}
	}
	else currentState = WANDER;
}
void AiModuleResident::run(){
	if (currentState == WANDER){
		wanderInsideResidence(*residence);
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.10f){
			currentState = GO_SLEEP;
		}
	}
	else if (currentState == GO_SLEEP){
		sleep(*bed);
	}
	else if (currentState == SLEEPING){
		if (engine::random.generator->getFloat(0.0f, 1.0f) < 0.05f){
			bed->operate(*owner->owner);
			currentState = WANDER;
		}
	}
}
