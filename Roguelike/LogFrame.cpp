#include "LogFrame.h"

bool LogFrame::handleKey(TCOD_key_t key){
	GuiFrame::handleKey(key);
	if (!isOpen) return true;
	return false;
}

void LogFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	blit();

	int y = 1;
	int maxY = console->getHeight() - 1;
	for (std::string message : messages){
		console->printRectEx(console->getWidth()/2, y, console->getWidth(), 1, TCOD_BKGND_NONE, TCOD_CENTER, message.c_str());
		float fadeAlpha = alphaFg - alphaFg / maxY * y;
		if (fadeAlpha < 0.1) fadeAlpha = 0.1;
		blit(1, y, console->getWidth() - 1, 1, bounds.start.x + 1, bounds.start.y + y, fadeAlpha, 0.0);
		++y;
	}
}

void LogFrame::addMessage(std::string message){
	messages.push_front(message);
	if (messages.size() == console->getHeight() - 1){
		messages.pop_back();
	}
}

//Add to buffer
void LogFrame::addToMessage(std::string message){
	buffer += message;
}

//Add to buffer and flush
void LogFrame::finishMessage(std::string message){
	addToMessage(message);
	addMessage(buffer);
	buffer.clear();
}