#pragma once
#include "GuiFrame.h"
#include <deque>

class LogFrame : public GuiFrame
{
private:
	std::string buffer; //For multi part message

public:	
	std::deque<std::string> messages; //Messages
	void addMessage(std::string);
	void addToMessage(std::string);
	void finishMessage(std::string);
	
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);

	LogFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg){};
};

