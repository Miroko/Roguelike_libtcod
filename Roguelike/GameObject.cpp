#include "GameObject.h"

GameObject::Type GameObject::getType(){
	return type;
}

bool GameObject::isCreature(){
	return(
		type == CREATURE);
}

bool GameObject::isWeapon(){
	return(
		type == WEAPON_MELEE ||
		type == WEAPON_RANGED);
}

bool GameObject::isArmor(){
	return(
		type == ARMOR_BODY ||
		type == ARMOR_HAND ||
		type == ARMOR_HEAD ||
		type == ARMOR_LEG);
}

bool GameObject::isEquipment(){
	return(
		isWeapon() ||
		isArmor() ||
		isAccessory());
}

bool GameObject::isAccessory(){
	return(
		type == ACCESSORY);
}

bool GameObject::isConsumable(){
	return(
		type == CONSUMABLE);
}

bool GameObject::isOperatable(){
	return(
		type == DOOR ||
		type == BED ||
		type == FORGE ||
		type == ANVIL ||
		type == ALCHEMY_TABLE);
}

bool GameObject::isTile(){
	return(
		type == FLOOR ||
		type == WALL ||
		type == PORTAL ||
		type == WATER);
}

void GameObject::render(int x, int y){
	glyph.render(x, y);
}

void GameObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){

}

void GameObject::renderToFrameLine(GuiFrame &frame, Rectangle &renderBounds, int offsetY){

}

std::string GameObject::getStatistics(){
	return "";
}

std::string GameObject::getDescription(){
	return name;
}