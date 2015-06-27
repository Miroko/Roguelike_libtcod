#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include <string>
#include <memory>
class GuiFrame
{
protected:
	const int MARGIN = 1;
	const TCODColor FRAME_COLOR = TCODColor::white;
	const TCODColor FG_COLOR = TCODColor::white;
	const TCODColor BG_COLOR = TCODColor::black;

	std::string title;

	std::shared_ptr<TCODConsole> console;

	//Screen bounds
	Rectangle screenBounds;

	char controlKey;
	float alphaFg;
	float alphaBg;

	int getWidth();
	int getHeight();

	//True if key handled
	virtual bool handleKey(TCOD_key_t key, bool &requireUpdate);
	virtual void render() = 0;
	void blit(int fromX, int fromY, int width, int height, int toX, int toY, float alphaFg, float alphaBg);
	void blit();

	virtual void onOpen();
	virtual void onClose();

	//Print string inside rectangle
	void printString(int x, int y, int width, int height, const TCODColor &fg, const TCODColor &bg, TCOD_alignment_t alignment, TCOD_bkgnd_flag_t bgFlag, std::string string);

public:
	bool isOpen;
	virtual void open();
	virtual void close();

	void init(Rectangle bounds);

	GuiFrame(char controlKey, bool open, float alphaFg = 1.0, float alphaBg = 1.0, std::string title = "") :
		controlKey(controlKey),
		isOpen(open),
		alphaFg(alphaFg),
		alphaBg(alphaBg),
		title(title){};
};

