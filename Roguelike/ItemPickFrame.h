#pragma once
#include "SelectableItemFrame.h"

class ItemPickFrame : public SelectableItemFrame
{
public:

	bool moveToInventory(std::shared_ptr<Item> item);

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> item);

	ItemPickFrame(std::string name, bool open, float alphaFg, float alphaBg) : SelectableItemFrame(name, open, alphaFg, alphaBg){};
};

