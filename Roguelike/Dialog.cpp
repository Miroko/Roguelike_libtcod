#include "Dialog.h"
#include "Engine.h"

const std::shared_ptr<Dialog> Dialog::DIALOG_END = nullptr;
const std::shared_ptr<Dialog> Dialog::NO_RESPONSE = std::shared_ptr<Dialog>(new DialogNoResponse());

void Dialog::setSpeaker(Creature &speaker){
	this->speaker = &speaker;
}
Creature &Dialog::getSpeaker(){
	return *speaker;
}
std::string Dialog::getText(){
	std::string text = "";
	for (auto &option : dialogOptions){
		text.append(option->getText(*speaker));
	}
	return text;
}
std::shared_ptr<Dialog> const &Dialog::getNextDialog(std::shared_ptr<DialogOption> &selectedOption){
	return selectedOption->getNextDialog(*speaker);
}

//No response
std::string DialogNoResponse::getText(){
	return speaker->name + " is not responding.\n\n" + Dialog::getText();
}

