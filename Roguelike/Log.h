#pragma once
#include "libtcod.hpp"
#include "GuiFrame.h"
#include <memory>
#include <deque>
class Log : public GuiFrame
{
private:
	std::string buffer; //For multi part message
public:	
	//Messages
	std::deque<std::string> messages;
	void addMessage(std::string);
	void addToMessage(std::string);
	void finishMessage(std::string);
	
	void GuiFrame::render(float elapsed);
	bool GuiFrame::handleKey(TCOD_key_t key);

	Log(std::string name, bool open, float alphaFg, float alphaBg) : GuiFrame(name, open, alphaFg, alphaBg){};
};

