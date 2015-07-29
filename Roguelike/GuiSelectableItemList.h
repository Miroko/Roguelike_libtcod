#pragma once
#include "libtcod.hpp"
#include "GuiComponent.h"
#include <vector>
#include <memory>
#include <string>
#include <functional>

class Item;
class ItemContainer;
class GuiSelectableItemList : public GuiComponent
{
public:
	ItemContainer *itemContainer = nullptr;
	int selectedRow = 0;
	int selectedOperation = 0;
	std::vector<std::string> operationsForSelectedItem;
	std::function<std::vector<std::string>(std::shared_ptr<Item>, bool selected)> getOperationsFunction;
	std::function<void(std::shared_ptr<Item>, std::string)> onOperationSelectedFunction;

	void setItemContainer(ItemContainer &container);
	void setGetOperationsFunction(std::function<std::vector<std::string>(std::shared_ptr<Item>, bool selected)> getOperations);
	void setOnOperationSelectedFunction(std::function<void(std::shared_ptr<Item>, std::string)> onOperationSelected);
	bool handleKey(TCOD_key_t &key);
	void updateSelection();
	void GuiComponent::renderTo(GuiFrame &frame, Rectangle &bounds);

	GuiSelectableItemList() : GuiComponent(){};
};

