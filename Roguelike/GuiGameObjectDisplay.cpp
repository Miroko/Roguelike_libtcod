#include "GuiGameObjectDisplay.h"
#include "GameObject.h"

void GuiGameObjectDisplay::setDisplayedObject(GameObject *object){
	objectInDisplay = object;
}

void GuiGameObjectDisplay::clear(){
	objectInDisplay = nullptr;
}

void GuiGameObjectDisplay::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (objectInDisplay){
		objectInDisplay->renderToFrame(frame, bounds);
	}
}