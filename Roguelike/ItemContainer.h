#pragma once
#include "Item.h"
#include <vector>
#include <memory>
template<typename T> class ItemContainer
{
public:
	std::vector<std::shared_ptr<T>> items;

	void ItemContainer<T>::add(std::shared_ptr<T> item){
		items.push_back(item);
	}

	void ItemContainer<T>::remove(T &item){
		auto currentItem = items.begin();
		while (currentItem != items.end()){
			if (currentItem->get() == &item){
				items.erase(currentItem);
				break;
			}
			else ++currentItem;
		}
	}
	ItemContainer(){};
};

