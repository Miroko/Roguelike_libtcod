#include "GameObject.h"

GameObject::Type GameObject::getType(){
	return type;
}

void GameObject::render(int x, int y){
	glyph.render(x, y);
}

std::string GameObject::getDescription(){
	return name;
}
