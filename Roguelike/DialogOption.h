#pragma once
#include "DynamicObject.h"
#include <memory>
#include <string>

const std::string DIALOG_OPTION_END = "End.";
const std::string DIALOG_OPTION_TRADE = "Trade.";

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

class OptionEnd : public DialogOption{
public:
	OptionEnd(std::shared_ptr<DynamicObject> &owner) : DialogOption("", DIALOG_OPTION_END){};
};

class OptionTrade : public DialogOption{
public:
	OptionTrade(std::shared_ptr<DynamicObject> &owner) : DialogOption(owner->name + " is willing to trade.\n\n", DIALOG_OPTION_TRADE, owner){};
	void onOptionSelect();
};


const std::shared_ptr<Dialog> DIALOG_END(nullptr);