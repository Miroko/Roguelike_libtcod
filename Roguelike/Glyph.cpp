#include "Glyph.h"

void Glyph::render(int x, int y){
	TCODConsole::root->setCharBackground(x, y, bgColor, bgFlag);
	TCODConsole::root->setCharForeground(x, y, fgColor);
	TCODConsole::root->setChar(x, y, character);
}


