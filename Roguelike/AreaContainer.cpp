#include "AreaContainer.h"
#include "DynamicObject.h"
#include "OperatableObject.h"
#include "Creature.h"
#include "Tile.h"

Item& AreaContainer::getItemToRender(int itemRenderNumberCurrent){
	int itemNumber = 0;
	for (int loop = 0; loop <= itemRenderNumberCurrent; ++loop){
		if (itemNumber == items.size() - 1) itemNumber = 0;
		else ++itemNumber;
	}
	return *items.at(itemNumber);
}

bool AreaContainer::isPassable(DynamicObject &dynamicObjectMoving){
	if (creature){
		return false;
	}
	if (!tile->isPassable(dynamicObjectMoving)){
		return false;
	}
	if (operatableObject){
		if (!operatableObject->isPassable(dynamicObjectMoving)) return false;
	}
	return true;
}

double AreaContainer::getTransparency(){
	if (creature){
		return creature->glyph.getTransparency();
	}
	if (operatableObject){
		return operatableObject->glyph.getTransparency();
	}
	else return tile->glyph.getTransparency();
}