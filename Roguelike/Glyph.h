#pragma once
#include "libtcod.hpp"

class Glyph
{
public:
	TCOD_bkgnd_flag_t bgFlag;

	TCODColor fgColor;
	TCODColor bgColor;

	char character;

	void render(int x, int y);

	Glyph(TCODColor bg, TCODColor fg, char character) : fgColor(fg), bgColor(bg), character(character){
		bgFlag = TCOD_BKGND_SET;
	};
	Glyph(TCODColor bg) : Glyph(bg, bg, ' '){

	};
	Glyph(char character, TCODColor fg) : fgColor(fg), character(character){
		bgFlag = TCOD_BKGND_NONE;
	};

	Glyph(){};
};

