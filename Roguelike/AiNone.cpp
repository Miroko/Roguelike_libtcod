#include "AiNone.h"

void AiNone::update(){
	calculateFov();
}

std::shared_ptr<CreatureAi> AiNone::copy(){
	return std::shared_ptr<CreatureAi>(new AiNone(*this));
}