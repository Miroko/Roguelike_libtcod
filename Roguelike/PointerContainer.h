#pragma once
#include "Item.h"
#include <vector>
#include <memory>
template<typename T> class PointerContainer
{
public:
	std::vector<std::shared_ptr<T>> items;

	void PointerContainer<T>::add(std::shared_ptr<T> &item){
		items.push_back(item);
	}

	void PointerContainer<T>::remove(T &item){
		auto currentItem = items.begin();
		while (currentItem != items.end()){
			if (currentItem->get() == &item){
				items.erase(currentItem);
				break;
			}
			else ++currentItem;
		}
	}
	PointerContainer(){};
};

