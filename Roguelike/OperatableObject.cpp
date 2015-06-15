#include "OperatableObject.h"

void OperatableObject::on(){
	isOn = true;
}

void OperatableObject::off(){
	isOn = false;
}

void OperatableObject::render(int x, int y){
	if (isOn){
		onGlyph.render(x, y);
	}
	else{
		offGlyph.render(x, y);
	}
}