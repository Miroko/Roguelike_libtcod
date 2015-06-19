#include "EquipmentFrame.h"
#include "Engine.h"

void EquipmentFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	if (operation == UNEQUIP) unequip(item);
}

void EquipmentFrame::unequip(std::shared_ptr<Item> &item){	
	if (item->type == Item::WEAPON_MELEE){
		if (weapon != nullptr){			
			Engine::GUI.inventory.addItem(weapon);			
			removeItem(weapon);
			Engine::playerController.playerCreature->weapon = nullptr;
			weapon = nullptr;
		}
	}
	else if (item->type == Item::ARMOR_HEAD){
		if (armorHead != nullptr){
			Engine::GUI.inventory.addItem(armorHead);
			removeItem(armorHead);
			Engine::playerController.playerCreature->armorHead = nullptr;
			armorHead = nullptr;
		}
	}
	else if (item->type == Item::ARMOR_BODY){
		if (armorBody != nullptr){
			Engine::GUI.inventory.addItem(armorBody);
			removeItem(armorBody);
			Engine::playerController.playerCreature->armorBody = nullptr;
			armorBody = nullptr;
		}
	}
	else if (item->type == Item::ARMOR_HAND){
		if (armorHand != nullptr){
			Engine::GUI.inventory.addItem(armorHand);
			removeItem(armorHand);
			Engine::playerController.playerCreature->armorHand = nullptr;
			armorHand = nullptr;
		}
	}
	else if (item->type == Item::ARMOR_LEG){
		if (armorLeg != nullptr){
			Engine::GUI.inventory.addItem(armorLeg);
			removeItem(armorLeg);
			Engine::playerController.playerCreature->armorLeg = nullptr;
			armorLeg = nullptr;
		}
	}
}

void EquipmentFrame::equip(std::shared_ptr<Item> &item){
	addItem(item);

	if (item->type == Item::WEAPON_MELEE){
		weapon = item;
		Engine::playerController.playerCreature->equip(weapon);
	}
	else if (item->type == Item::ARMOR_HEAD){
		armorHead = item;
		Engine::playerController.playerCreature->equip(armorHead);
	}
	else if (item->type == Item::ARMOR_BODY){
		armorBody = item;
		Engine::playerController.playerCreature->equip(armorBody);
	}
	else if (item->type == Item::ARMOR_HAND){
		armorHand = item;
		Engine::playerController.playerCreature->equip(armorHand);
	}
	else if (item->type == Item::ARMOR_LEG){
		armorLeg = item;
		Engine::playerController.playerCreature->equip(armorLeg);
	}
}

std::vector<std::string> EquipmentFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	return EQUIPMENT_OPERATIONS;
}