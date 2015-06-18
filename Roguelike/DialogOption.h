#pragma once
#include "DynamicObject.h"
#include <memory>
#include <string>

class Dialog;
class DialogOption
{
public:
	std::string text;
	std::string optionText;
	std::shared_ptr<DynamicObject> owner;

	virtual void onOptionSelect();
	virtual std::shared_ptr<Dialog> getNextDialog(std::shared_ptr<DynamicObject> &owner);

	DialogOption(std::string text, const std::string &optionText, std::shared_ptr<DynamicObject> &owner = std::shared_ptr<DynamicObject>(nullptr)) : text(text), optionText(optionText), owner(owner){};
};

const std::shared_ptr<Dialog> DIALOG_END(nullptr);