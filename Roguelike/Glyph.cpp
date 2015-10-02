#include "Glyph.h"

void Glyph::render(int x, int y, double lightIntensity){
	TCODConsole::root->setCharBackground(x, y, bgColor * lightIntensity, bgFlag);
	TCODConsole::root->setCharForeground(x, y, fgColor * lightIntensity);
	TCODConsole::root->setChar(x, y, character);
}



