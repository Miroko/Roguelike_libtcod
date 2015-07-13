#pragma once
#include "DialogOption.h"
#include "DynamicObject.h"
#include <memory>

class Dialog
{
protected:
	Creature *speaker;

public:
	static const std::shared_ptr<Dialog> DIALOG_END;
	static const std::shared_ptr<Dialog> NO_RESPONSE;

	virtual std::string getText();
	std::vector<std::shared_ptr<DialogOption>> dialogOptions;

	void setSpeaker(Creature &speaker);
	Creature &getSpeaker();
	std::shared_ptr<Dialog> const &getNextDialog(std::shared_ptr<DialogOption> &selectedOption);

	Dialog(std::vector<std::shared_ptr<DialogOption>> &dialogOptions) : dialogOptions(dialogOptions){};
};

class DialogNoResponse : public Dialog{
public:
	std::string getText();

	DialogNoResponse() : Dialog(std::vector<std::shared_ptr<DialogOption>>({
		std::shared_ptr<DialogOption>(new OptionEnd())
	})){};
};