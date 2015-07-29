#include "GuiBox.h"
#include "GuiFrame.h"

void GuiBox::renderTo(GuiFrame &frame, Rectangle &bounds){
	if (title != ""){
		frame.console->printFrame(
			bounds.start.x, bounds.start.y,
			bounds.getWidth() - 1, bounds.getHeight(),
			false, TCOD_BKGND_DEFAULT, title.c_str());
	}
	else{
		frame.console->printFrame(
			bounds.start.x, bounds.start.y, 
			bounds.getWidth() - 1, bounds.getHeight(), 
			false, TCOD_BKGND_DEFAULT);
	}
}