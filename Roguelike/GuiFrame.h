#pragma once
#include "libtcod.hpp"
#include "Rectangle.h"
#include <string>
#include <memory>
class GuiFrame
{
public:
	const TCODColor FRAME_COLOR = TCODColor::white;
	const TCODColor FG_COLOR = TCODColor::white;
	const TCODColor BG_COLOR = TCODColor::black;

	Rectangle bounds = Rectangle(Point2D(0, 0), Point2D(30, 30));
	std::shared_ptr<TCODConsole> console = std::shared_ptr<TCODConsole>(new TCODConsole(bounds.getWidth(), bounds.getHeight()));

	std::string name;
	bool open;
	float alphaFg;
	float alphaBg;

	virtual void openClose();

	void resize(Rectangle &bounds);
	
	//True if require update
	virtual bool handleKey(TCOD_key_t key) = 0;
	virtual void render(float elapsed) = 0;
	void blit(int fromX, int fromY, int width, int height, int toX, int toY, float alphaFg, float alphaBg);
	void blit();

	GuiFrame(std::string name, bool open, float alphaFg = 1.0, float alphaBg = 1.0) :
		name(name), open(open), alphaFg(alphaFg), alphaBg(alphaBg){};
};

