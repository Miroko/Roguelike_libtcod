#pragma once
#include "SelectableItemFrame.h"
#include "Equipment.h"

class EquipmentFrame : public SelectableItemFrame
{
private:
	const std::string UNEQUIP = "Unequip";
	const std::vector<std::string> EQUIPMENT_OPERATIONS = std::vector<std::string>({ UNEQUIP });

public:
	void onOpen();
	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation);
	std::vector<std::string> SelectableItemFrame::getOperationsForItem(std::shared_ptr<Item> &item);

	EquipmentFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		SelectableItemFrame(controlKey, open, alphaFg, alphaBg, "Equipment"){};
};