#include "Log.h"

bool Log::handleKey(TCOD_key_t key){
	return false;
}

void Log::render(float elapsed){
	GuiFrame::render(elapsed);

	blit();

	int y = 1;
	int maxY = console->getHeight() - 1;
	for (std::string message : messages){
		console->printRectEx(console->getWidth()/2, y, console->getWidth(), 1, TCOD_BKGND_DEFAULT, TCOD_CENTER, message.c_str());
		alphaFg = 1.0 - alphaFg / (maxY-2) * y;
		if (alphaFg < 0.1) alphaFg = 0.1;
		blit(1, y, console->getWidth() - 2, 1, 1, bounds.start.y + y);
		alphaFg = 1.0;
		++y;
	}
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