#pragma once
#include "DialogOption.h"
#include "DynamicObject.h"
#include <memory>

class Dialog
{
private:
	std::shared_ptr<DynamicObject> speaker;

public:
	static const std::shared_ptr<Dialog> END;
	static const std::shared_ptr<Dialog> NO_RESPONSE;

	std::string getText();
	std::vector<std::shared_ptr<DialogOption>> &dialogOptions;

	void setSpeaker(DynamicObject &speaker);
	std::shared_ptr<DynamicObject> const &getSpeaker();
	std::shared_ptr<Dialog> const &getNextDialog(std::shared_ptr<DialogOption> &selectedOption);

	Dialog(std::vector<std::shared_ptr<DialogOption>> &dialogOptions) : dialogOptions(dialogOptions){};
};

class DialogNoResponse : public Dialog{
	class OptionNoResponse : public DialogOption{
	private:
		void DialogOption::onOptionSelect(DynamicObject &speaker);

	public:
		std::string DialogOption::getText(DynamicObject &speaker);
		std::string DialogOption::getOptionText(DynamicObject &speaker);
		std::shared_ptr<Dialog> const &DialogOption::getNextDialog(DynamicObject &speaker);

		OptionNoResponse() : DialogOption(){};
	};
public:
	DialogNoResponse() : Dialog(std::vector<std::shared_ptr<DialogOption>>({
		std::make_shared<OptionNoResponse>(OptionNoResponse())
	})){};
};