#include "GuiFrame.h"

void GuiFrame::render(float elapsed){
	console->setDefaultForeground(FRAME_COLOR);
	console->setDefaultBackground(BG_COLOR);
	console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET, name.c_str());
	console->setDefaultForeground(FG_COLOR);
}

void GuiFrame::blit(int x, int y, int width, int height, int toX, int toY, float alphaFg, float alphaBg){
	TCODConsole::blit(console.get(), x, y, width, height,
		TCODConsole::root, toX, toY, alphaFg, alphaBg);
}

void GuiFrame::blit(){
	blit(0, 0, console->getWidth(), console->getHeight(), bounds.start.x, bounds.start.y, alphaFg, alphaBg);
}

void GuiFrame::openClose(){
	open = !open;
}

void GuiFrame::resize(Rectangle &bounds){
	this->bounds = bounds;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(bounds.getWidth(), bounds.getHeight()));
}