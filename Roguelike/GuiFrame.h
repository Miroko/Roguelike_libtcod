#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include <string>
#include <memory>

class GuiFrame
{
protected:
	std::string title;
	Rectangle frameBounds;

	char controlKey;
	float alphaFg;
	float alphaBg;

	//True if key handled
	void blit(int fromX, int fromY, int width, int height, int toX, int toY, float alphaFg, float alphaBg);
	void blit();

	virtual void onOpen();
	virtual void onClose();

public:
	std::shared_ptr<TCODConsole> console;

	bool isOpen;
	virtual void open();
	virtual void close();

	int getWidth();
	int getHeight();

	//Print string inside rectangle
	void printString(int x, int y, int width, int height, const TCODColor &fg, const TCODColor &bg, TCOD_alignment_t alignment, TCOD_bkgnd_flag_t bgFlag, std::string string);
	void printString(int x, int y, int width, int height, const TCODColor &fg, TCOD_alignment_t alignment, std::string string);
	void paintBg(int x, int y, int width, int height, const TCODColor &color);

	void init(Rectangle bounds);

	virtual bool handleKey(TCOD_key_t &key);
	virtual void render() = 0;
	virtual void update();

	GuiFrame(char controlKey, bool open, float alphaFg = 1.0, float alphaBg = 1.0, std::string title = "") :
		controlKey(controlKey),
		isOpen(open),
		alphaFg(alphaFg),
		alphaBg(alphaBg),
		title(title){};
};

