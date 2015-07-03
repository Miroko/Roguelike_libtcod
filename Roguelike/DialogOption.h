#pragma once
#include "DynamicObject.h"
#include "QuestPhase.h"
#include <memory>
#include <string>

class Dialog;
class DialogOption
{
private:
	virtual void onOptionSelect(DynamicObject &speaker) = 0;

public:
	virtual std::string getText(DynamicObject &speaker) = 0;
	virtual std::string getOptionText(DynamicObject &speaker) = 0;
	virtual std::shared_ptr<Dialog> const &getNextDialog(DynamicObject &owner) = 0;

	DialogOption(){};
};

class OptionEnd : public DialogOption{
private:
	void DialogOption::onOptionSelect(DynamicObject &speaker);

public:
	std::string DialogOption::getText(DynamicObject &speaker);
	std::string DialogOption::getOptionText(DynamicObject &speaker);
	std::shared_ptr<Dialog> const &DialogOption::getNextDialog(DynamicObject &speaker);

	OptionEnd() : DialogOption(){};
};

class OptionTrade : public DialogOption{
private:
	void DialogOption::onOptionSelect(DynamicObject &speaker);

public:
	std::string DialogOption::getText(DynamicObject &speaker);
	std::string DialogOption::getOptionText(DynamicObject &speaker);
	std::shared_ptr<Dialog> const &DialogOption::getNextDialog(DynamicObject &speaker);

	OptionTrade() : DialogOption(){};
};
