#pragma once
#include "PlayerController.h"
#include "PlayerInventory.h"

class Creature;
class PlayerHandler
{
private:
	std::shared_ptr<Creature> playerCreature;

public:
	PlayerController playerController;
	PlayerInventory playerInventory;

	void setPlayerCreature(std::shared_ptr<Creature> creature);
	std::shared_ptr<Creature> const &getPlayerCreature();


	PlayerHandler(){};
};

