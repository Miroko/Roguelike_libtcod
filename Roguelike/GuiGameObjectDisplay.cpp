#include "GuiGameObjectDisplay.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Creature.h"
#include "Tile.h"
#include "Consumable.h"
#include "OperatableObject.h"

void GuiGameObjectDisplay::setDisplayedObject(GameObject *object){
	clear();
	if (object != nullptr){
		if (object->type == GameObject::CREATURE) guiCreature.setCurrentCreature(static_cast<Creature*>(object));
		else if (object->isWeapon()) guiWeapon.setCurrentWeapon(static_cast<Weapon*>(object));
		else if (object->isArmor()) guiArmor.setCurrentArmor(static_cast<Armor*>(object));
		else if (object->isConsumable()) guiConsumable.setCurrentConsumable(static_cast<Consumable*>(object));
		else if (object->isOperatable()) guiOperatable.setCurrentOperatable(static_cast<OperatableObject*>(object));
		else if (object->isTile()) guiTile.setCurrentTile(static_cast<Tile*>(object));
	}
}

void GuiGameObjectDisplay::clear(){
	guiCreature.setCurrentCreature(nullptr);
	guiArmor.setCurrentArmor(nullptr);
	guiWeapon.setCurrentWeapon(nullptr);
	guiConsumable.setCurrentConsumable(nullptr);
	guiOperatable.setCurrentOperatable(nullptr);
	guiTile.setCurrentTile(nullptr);
}

void GuiGameObjectDisplay::renderTo(GuiFrame &frame, Rectangle &bounds){
	guiCreature.renderTo(frame, bounds);
	guiArmor.renderTo(frame, bounds);
	guiWeapon.renderTo(frame, bounds);
	guiConsumable.renderTo(frame, bounds);
	guiOperatable.renderTo(frame, bounds);
	guiTile.renderTo(frame, bounds);
}