#include "Quest.h"

std::shared_ptr<QuestPhase> const &Quest::getCurrentPhase(){
	return currentPhase;
}

void Quest::setCurrentPhase(std::shared_ptr<QuestPhase> phase){
	currentPhase = phase;
}

std::shared_ptr<QuestPhase> const &Quest::getVillage(){
	return village;
}
