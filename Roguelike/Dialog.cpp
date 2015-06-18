#include "Dialog.h"

std::shared_ptr<Dialog> Dialog::getNextDialog(std::shared_ptr<DialogOption> &dialogOption){
	dialogOption->onOptionSelect();
	return dialogOption->getNextDialog(dialogOption->owner);
}

std::string Dialog::getText(){
	std::string text;
	for (auto &option : dialogOptions){
		text.append(option->text);
	}
	return text;
}
