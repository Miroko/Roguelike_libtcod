#pragma once
#include "SelectableItemFrame.h"
#include "Equipment.h"
class EquipmentFrame : public SelectableItemFrame
{
private:
	const std::string UNEQUIP = "Unequip";
	const std::vector<std::string> EQUIPMENT_OPERATIONS = std::vector<std::string>({ UNEQUIP });

	std::shared_ptr<Item> weapon = std::shared_ptr<Item>();
public:
	void equip(std::shared_ptr<Item> &item);
	void unequip(std::shared_ptr<Item> &item);

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation);
	std::vector<std::string> SelectableItemFrame::getOperationsForItem(std::shared_ptr<Item> &item);

	EquipmentFrame(std::string name, char controlKey, bool open, float alphaFg, float alphaBg) : SelectableItemFrame(name, controlKey, open, alphaFg, alphaBg){};
};