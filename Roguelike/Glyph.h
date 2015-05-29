#pragma once
#include "libtcod.hpp"
class Glyph
{
	TCOD_bkgnd_flag_t bgFlag;

	TCODColor fgColor;
	TCODColor bgColor;
	char character;
public:
	void render(int x, int y);

	Glyph(TCODColor fg, TCODColor bg, char character) :
		fgColor(fg), bgColor(bg), character(character){
		bgFlag = TCOD_BKGND_SET;
	};
	Glyph(TCODColor fg, char character) : fgColor(fg), character(character){
		bgFlag = TCOD_BKGND_NONE;
	};

	Glyph(){};
};

