#include "Item.h"

bool Item::operator==(const Item &item){
	if (this == &item) return true;
	else return false;
}