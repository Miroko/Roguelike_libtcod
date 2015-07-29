#include "GuiFrame.h"
#include "KeyMapping.h"
#include "Gui.h"

void GuiFrame::render(){
	console->setDefaultForeground(Gui::FRAME_FG);
	console->setDefaultBackground(Gui::FRAME_BG);
	if (title == ""){
		console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET);
	}
	else{
		console->printFrame(0, 0, console->getWidth(), console->getHeight(), true, TCOD_BKGND_SET, title.c_str());
	}
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

bool GuiFrame::handleKey(TCOD_key_t &key){
	if (controlKey != KEY_UNDEFINED){
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
	std::string coloredString = "%c" + string + "%c";

	if (alignment == TCOD_LEFT){
		x += Gui::FRAME_MARGIN + 1;
		y += Gui::FRAME_MARGIN + 1;
		width -= Gui::FRAME_MARGIN - 2;
		height -= Gui::FRAME_MARGIN - 2;
	}
	else if (alignment == TCOD_CENTER){
		x += width/2 + 2;
		y += Gui::FRAME_MARGIN + 1;
		width -= Gui::FRAME_MARGIN + 3;
		height -= Gui::FRAME_MARGIN - 2;
	}
	else if (alignment == TCOD_RIGHT){
		x -= Gui::FRAME_MARGIN - width - 3;
		y += Gui::FRAME_MARGIN + 1;
		width -= Gui::FRAME_MARGIN - 2;
		height -= Gui::FRAME_MARGIN - 2;
	}
	console->printRectEx(
		x, y,
		width, height,
		bgFlag, alignment, coloredString.c_str(),
		TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
}

void GuiFrame::printString(int x, int y, int width, int height, const TCODColor &fg, TCOD_alignment_t alignment, std::string string){
	printString(x, y, width, height, fg, fg, alignment, TCOD_BKGND_NONE, string);
}

void GuiFrame::paintBg(int x, int y, int width, int height, const TCODColor &color){
	x += Gui::FRAME_MARGIN + 1;
	y += Gui::FRAME_MARGIN + 1;
	width -= Gui::FRAME_MARGIN - 2;
	height -= Gui::FRAME_MARGIN - 2;
	for (int consoleX = x; consoleX < x + width; ++consoleX){
		for (int consoleY = y; consoleY < y + height; ++consoleY){
			console->setCharBackground(consoleX, consoleY, color);
		}
	}
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
	return screenBounds.getWidth() - Gui::FRAME_MARGIN - 5;
}

int GuiFrame::getHeight(){
	return screenBounds.getHeight() - Gui::FRAME_MARGIN - 5;
}

void GuiFrame::init(Rectangle bounds){
	screenBounds = bounds;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(screenBounds.getWidth(), screenBounds.getHeight()));
}