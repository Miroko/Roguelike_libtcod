#include "Quest.h"

void Quest::setCurrentPhase(std::shared_ptr<QuestPhase> phase){
	currentPhase = phase;
}
std::shared_ptr<QuestPhase> const &Quest::getNextPhase(){
	currentPhaseIndex++;
	if (currentPhaseIndex == phases.size()){
		currentPhaseIndex = 0;
		return getVillage();
	}
	else return phases.at(currentPhaseIndex);
}
std::shared_ptr<QuestPhase> const &Quest::getVillage(){
	return village;
}
std::shared_ptr<QuestPhase> const &Quest::getCurrentPhase(){
	return currentPhase;
}

