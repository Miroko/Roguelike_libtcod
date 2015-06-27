#pragma once
#include "SelectableItemFrame.h"
#include "Equipment.h"
class EquipmentFrame : public SelectableItemFrame
{
private:
	const std::string UNEQUIP = "Unequip";
	const std::vector<std::string> EQUIPMENT_OPERATIONS = std::vector<std::string>({ UNEQUIP });

	std::shared_ptr<Item> weapon = nullptr;
	std::shared_ptr<Item> armorHead = nullptr;
	std::shared_ptr<Item> armorBody = nullptr;
	std::shared_ptr<Item> armorHand = nullptr;
	std::shared_ptr<Item> armorLeg = nullptr;
public:
	void equip(std::shared_ptr<Item> &equipment);
	void unequip(std::shared_ptr<Item> &equipment);

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation);
	std::vector<std::string> SelectableItemFrame::getOperationsForItem(std::shared_ptr<Item> &item);

	EquipmentFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		SelectableItemFrame(controlKey, open, alphaFg, alphaBg, "Equipment"){};
};