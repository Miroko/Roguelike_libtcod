#pragma once
#include "libtcod.hpp"
#include "GuiFrame.h"
#include <memory>
#include <deque>
class LogFrame : public GuiFrame
{
private:
	std::string buffer; //For multi part message
public:	
	//Messages
	std::deque<std::string> messages;
	void addMessage(std::string);
	void addToMessage(std::string);
	void finishMessage(std::string);
	
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key, bool &requireUpdate);

	LogFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Log"){};
};

