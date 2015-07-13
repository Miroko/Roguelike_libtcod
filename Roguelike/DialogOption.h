#pragma once
#include "QuestPhase.h"
#include <memory>
#include <string>

class Creature;
class Dialog;
class DialogOption
{
private:
	virtual void onOptionSelect(Creature &speaker) = 0;

public:
	static const std::shared_ptr<DialogOption> END;
	static const std::shared_ptr<DialogOption> TRADE;

	virtual std::string getText(Creature &speaker) = 0;
	virtual std::string getOptionText(Creature &speaker) = 0;
	virtual std::shared_ptr<Dialog> const &getNextDialog(Creature &owner) = 0;

	DialogOption(){};
};

class OptionEnd : public DialogOption{
private:
	void DialogOption::onOptionSelect(Creature &speaker);

public:
	std::string DialogOption::getText(Creature &speaker);
	std::string DialogOption::getOptionText(Creature &speaker);
	std::shared_ptr<Dialog> const &DialogOption::getNextDialog(Creature &speaker);

	OptionEnd() : DialogOption(){};
};

class OptionTrade : public DialogOption{
private:
	void DialogOption::onOptionSelect(Creature &speaker);

public:
	std::string DialogOption::getText(Creature &speaker);
	std::string DialogOption::getOptionText(Creature &speaker);
	std::shared_ptr<Dialog> const &DialogOption::getNextDialog(Creature &speaker);

	OptionTrade() : DialogOption(){};
};
