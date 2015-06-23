#include "QuestPhase.h"
#include "Engine.h"

void QuestPhase::placePlayer(){
	Engine::area.placeAliveObject(Engine::playerController.playerCreature, Engine::area.bounds.getCenterPoint());
}
