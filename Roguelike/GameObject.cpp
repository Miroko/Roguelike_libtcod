#include "GameObject.h"

void GameObject::render(int x, int y){
	glyph.render(x, y);
}

std::string GameObject::getDescription(){
	return name;
}

bool GameObject::passable(){
	return false;
}

