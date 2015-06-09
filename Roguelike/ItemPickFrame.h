#pragma once
#include "SelectableItemFrame.h"

class ItemPickFrame : public SelectableItemFrame<Item>
{
public:
	bool moveToInventory(std::shared_ptr<Item> item);

	void SelectableItemFrame<Item>::onItemSelect(std::shared_ptr<Item> item);

	ItemPickFrame(std::string name, bool open, float alphaFg, float alphaBg) : SelectableItemFrame<Item>(name, open, alphaFg, alphaBg){};
};

