#include "Log.h"

void Log::init(bool open){
	isOpen = open;
	console = std::shared_ptr<TCODConsole>(new TCODConsole(TCODConsole::root->getWidth(), TCODConsole::root->getHeight() * 0.25));
}

void Log::openOrClose(){
	isOpen = !isOpen;
}

void Log::render(){
	console->setDefaultForeground(TCODColor::white);
	console->printFrame(0, 0, console->getWidth(), console->getHeight());
	
	console->setDefaultForeground(TCODColor::white);
	int y = 1;
	for (std::string message : messages){
		console->printRect(1, y, console->getWidth(), 1, message.c_str());
		y++;
	}

	TCODConsole::blit(console.get(), 0, 0, console->getWidth(), console->getHeight(), TCODConsole::root, 0, TCODConsole::root->getHeight() - console->getHeight());
}

void Log::addMessage(std::string message){
	messages.push_front(message);
	if (messages.size() == console->getHeight() - 1){
		messages.pop_back();
	}
}

//Add to buffer
void Log::addToMessage(std::string message){
	buffer += message;
}

//Add to buffer and flush
void Log::finishMessage(std::string message){
	addToMessage(message);
	addMessage(buffer);
	buffer.clear();
}