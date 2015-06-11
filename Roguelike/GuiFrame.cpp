#include "GuiFrame.h"
#include "KeyMapping.h"

void GuiFrame::render(float elapsed){
	console->setDefaultForeground(FRAME_COLOR);
	console->setDefaultBackground(BG_COLOR);
	if (name == "") console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET);
	else console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET, name.c_str());
	console->setDefaultForeground(FG_COLOR);
}

void GuiFrame::blit(int x, int y, int width, int height, int toX, int toY, float alphaFg, float alphaBg){
	TCODConsole::blit(console.get(), x, y, width, height,
		TCODConsole::root, toX, toY, alphaFg, alphaBg);
}

void GuiFrame::blit(){
	blit(0, 0, console->getWidth(), console->getHeight(), bounds.start.x, bounds.start.y, alphaFg, alphaBg);
}

//True == opened
bool GuiFrame::handleKey(TCOD_key_t key){
	if (key.c == controlKey){
		if (isOpen) close();
		else open();
	}
	return isOpen;	
}

void GuiFrame::open(){
	isOpen = true;
	onOpen();
}

void GuiFrame::close(){
	isOpen = false;
	onClose();
}

void GuiFrame::onOpen(){
	
}

void GuiFrame::onClose(){
	
}

void GuiFrame::resize(Rectangle &bounds){
	this->bounds = bounds;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(bounds.getWidth(), bounds.getHeight()));
}