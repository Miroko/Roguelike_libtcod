#pragma once
#include <list>
#include <memory>

class Item;
class ItemContainer
{
public:
	std::list<std::shared_ptr<Item>> items;

	void add(std::shared_ptr<Item> item);
	void remove(std::shared_ptr<Item> item);
	void removeAll();
	bool contains(std::shared_ptr<Item> item);

	std::shared_ptr<Item> getAt(int index);

	void sort();

	ItemContainer(std::list<std::shared_ptr<Item>> items) : items(items){};
	ItemContainer(){};
};

