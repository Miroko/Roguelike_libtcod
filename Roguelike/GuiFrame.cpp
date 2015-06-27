#include "GuiFrame.h"
#include "KeyMapping.h"

void GuiFrame::render(){
	console->setDefaultForeground(FRAME_COLOR);
	console->setDefaultBackground(BG_COLOR);
	if (title == ""){
		console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET);
	}
	else{
		console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET, title.c_str());
	}
	console->setDefaultForeground(FG_COLOR);
}

void GuiFrame::blit(int x, int y, int width, int height, int toX, int toY, float alphaFg, float alphaBg){
	TCODConsole::blit(
		console.get(), x, y, width, height,
		TCODConsole::root, toX, toY, alphaFg, alphaBg
		);
}

void GuiFrame::blit(){
	blit(
		0, 0, console->getWidth(), console->getHeight(),
		screenBounds.start.x, screenBounds.start.y,
		alphaFg, alphaBg
		);
}

bool GuiFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	if (controlKey != UNDEFINED){
		if (key.c == controlKey){
			if (isOpen) close();
			else open();
			return true;
		}
	}
	return false;	
}

void GuiFrame::printString(int x, int y, int width, int height, const TCODColor &fg, const TCODColor &bg, TCOD_alignment_t alignment, TCOD_bkgnd_flag_t bgFlag, std::string string){
	TCODConsole::setColorControl(TCOD_COLCTRL_1, fg, bg);
	std::string coloredString = "%c" + string + "%c ";

	if (alignment == TCOD_LEFT){
		x += MARGIN + 1;
		y += MARGIN + 1;
		width -= MARGIN - 2;
		height -= MARGIN - 2;
	}
	else if (alignment == TCOD_CENTER){
		x += width/2 + 2;
		y += MARGIN + 1;
		width -= MARGIN + 3;
		height -= MARGIN - 2;
	}
	else if (alignment == TCOD_RIGHT){
		x -= MARGIN - width - 4;
		y += MARGIN + 1;
		width -= MARGIN - 2;
		height -= MARGIN - 2;
	}
	console->printRectEx(
		x, y,
		width, height,
		bgFlag, alignment, coloredString.c_str(),
		TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
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

int GuiFrame::getWidth(){
	return console->getWidth() - MARGIN - 4;
}

int GuiFrame::getHeight(){
	return console->getHeight() - MARGIN - 4;
}

void GuiFrame::init(Rectangle bounds){
	screenBounds = bounds;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(screenBounds.getWidth(), screenBounds.getHeight()));
}