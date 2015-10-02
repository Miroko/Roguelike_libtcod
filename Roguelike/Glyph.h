#pragma once
#include "libtcod.hpp"

class Glyph
{
private:
	TCOD_bkgnd_flag_t bgFlag;
	char character;
	double transparency;

public:
	TCODColor fgColor;
	TCODColor bgColor;

	double getTransparency(){ return transparency; } // 0.0 <-> 1.0 // 0.0 == fully transparent for fov calculations

	void render(int x, int y, double lightIntensity);

	Glyph(TCODColor bg, TCODColor fg, char character = ' ', double transparency = 0.0) :
		fgColor(fg),
		bgColor(bg),
		character(character),
		transparency(transparency),
		bgFlag(TCOD_BKGND_SET){};

	Glyph(TCODColor bg, double transparency = 0.0) :
		Glyph(bg, bg, ' ', transparency){};

	Glyph(char character, TCODColor fg, double transparency = 0.0) :
		fgColor(fg),
		character(character),
		transparency(transparency),
		bgFlag(TCOD_BKGND_NONE){};

	Glyph(){};
};

