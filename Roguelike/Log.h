#pragma once
#include "libtcod.hpp"
#include <memory>
#include <deque>
class Log
{
private:
	std::string buffer; //For multi part message
public:	
	//Messages
	std::deque<std::string> messages;
	void addMessage(std::string);
	void addToMessage(std::string);
	void finishMessage(std::string);
	
	//GUI
	bool isOpen;
	std::shared_ptr<TCODConsole> console;
	void init();
	void openOrClose();
	void render();

	Log(){};
};

