#pragma once
#include "SelectableItemFrame.h"

class ItemPickFrame : public SelectableItemFrame
{
private:
	const std::vector<std::string> PICK_OPERATIONS = std::vector<std::string>({ "Take" });
public:
	bool moveToInventory(std::shared_ptr<Item> &item);

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation);
	std::vector<std::string> SelectableItemFrame::getOperationsForItem(std::shared_ptr<Item> &item);
	void onClose();

	ItemPickFrame(std::string name, char controlKey, bool open, float alphaFg, float alphaBg) : SelectableItemFrame(name, controlKey, open, alphaFg, alphaBg){};
};

