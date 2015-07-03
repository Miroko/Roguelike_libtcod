#include "PlayerHandler.h"

void PlayerHandler::setPlayerCreature(std::shared_ptr<Creature> creature){
	playerCreature = creature;
}

std::shared_ptr<Creature> const &PlayerHandler::getPlayerCreature(){
	return playerCreature;
}