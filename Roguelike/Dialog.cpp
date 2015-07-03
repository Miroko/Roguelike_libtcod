#include "Dialog.h"
#include "Engine.h"

const std::shared_ptr<Dialog> Dialog::END = nullptr;
const std::shared_ptr<Dialog> Dialog::NO_RESPONSE = std::make_shared<Dialog>(DialogNoResponse());

void Dialog::setSpeaker(DynamicObject &speaker){
	this->speaker.reset(&speaker);
}
std::shared_ptr<DynamicObject> const &Dialog::getSpeaker(){
	return speaker;
}
std::string Dialog::getText(){
	std::string text;
	for (auto &option : dialogOptions){
		text.append(option->getText(*speaker));
	}
	return text;
}
std::shared_ptr<Dialog> const &Dialog::getNextDialog(std::shared_ptr<DialogOption> &selectedOption){
	return selectedOption->getNextDialog(*speaker);
}

//No response
void DialogNoResponse::OptionNoResponse::onOptionSelect(DynamicObject &speaker){
	//Do nothing
}
std::string DialogNoResponse::OptionNoResponse::getText(DynamicObject &speaker){
	return speaker.name + " is not respoding.\n\n";
}
std::string DialogNoResponse::OptionNoResponse::getOptionText(DynamicObject &speaker){
	return engine::string.DIALOG_OPTION_END;
}
std::shared_ptr<Dialog> const &DialogNoResponse::OptionNoResponse::getNextDialog(DynamicObject &speaker){
	onOptionSelect(speaker);
	return END;
}