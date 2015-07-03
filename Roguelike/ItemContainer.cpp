#include "ItemContainer.h"

void ItemContainer::add(std::shared_ptr<Item> item){
	items.push_back(item);
}

void ItemContainer::remove(std::shared_ptr<Item> item){
	items.remove(item);
}

void ItemContainer::removeAll(){
	items.clear();
}

std::shared_ptr<Item> ItemContainer::getAt(int index){
	auto &iterator = items.begin();
	std::advance(iterator, index);
	return *iterator;
}

bool ItemContainer::contains(std::shared_ptr<Item> item){
	for (auto &o : items){
		if (o == item){
			return true;
		}
	}
	return false;
}

void ItemContainer::sort(){
	items.sort([](const std::shared_ptr<Item> &a, const std::shared_ptr<Item> &b){
		return a->name.compare(b->name);
	});
}