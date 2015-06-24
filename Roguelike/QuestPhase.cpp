#include "QuestPhase.h"
#include "Engine.h"

void QuestPhase::placePlayer(){
	Engine::area.placeCreature(Engine::playerController.playerCreature, Engine::area.bounds.getCenterPoint());
}
