#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include <string>
#include <memory>
class GuiFrame
{
public:
	const TCODColor FRAME_COLOR = TCODColor::white;
	const TCODColor TEXT_COLOR = TCODColor::white;

	Rectangle bounds = Rectangle(Point2D(0, 0), Point2D(30, 30));
	std::shared_ptr<TCODConsole> console = std::shared_ptr<TCODConsole>(new TCODConsole(bounds.getWidth(), bounds.getHeight()));

	std::string name;
	bool open;
	float alphaFg;
	float alphaBg;

	void openClose();

	void resize(Rectangle &bounds);
	
	//True if require update
	virtual bool handleKey(TCOD_key_t key) = 0;
	virtual void render(float elapsed) = 0;
	void blit(int x, int y, int width, int height, int toX, int toY);
	void blit();

	GuiFrame(std::string name, bool open, float alphaFg, float alphaBg) : name(name), open(open), alphaFg(alphaFg), alphaBg(alphaBg){};
};

