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
	//by
	//1. rarity
	//2. name
	//3. value
	items.sort([](const std::shared_ptr<Item> &a, const std::shared_ptr<Item> &b){
		if (a->rarity.prevalence >= b->rarity.prevalence){
			if (a->rarity.prevalence == b->rarity.prevalence){
				int comparisonName = b->name.compare(a->name);
				if (comparisonName < 0){
					return false;
				}
				else if(comparisonName == 0){
					if (a->getValue() <= b->getValue()){
						return false;
					}
					return true;
				}
				else{
					return true;
				}
			}
			return false;
		}
		return true;
	});
}