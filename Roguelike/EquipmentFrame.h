#pragma once
#include "SelectableItemFrame.h"
#include "Equipment.h"
class EquipmentFrame : public SelectableItemFrame<Equipment>
{
public:
	void SelectableItemFrame<Equipment>::onItemSelect(std::shared_ptr<Equipment> equipment);

	EquipmentFrame(std::string name, bool open, float alphaFg, float alphaBg) : SelectableItemFrame<Equipment>(name, open, alphaFg, alphaBg){};
};

