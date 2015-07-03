#include "AiNone.h"


void AiNone::initAi(Creature &owner){
	CreatureAi::initAi(owner);
}

void AiNone::update(){
	calculateFov();
}