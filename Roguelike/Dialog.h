#pragma once
#include "DialogOption.h"
#include "DynamicObject.h"
#include <memory>

class Dialog
{
public:
	std::vector<std::shared_ptr<DialogOption>> dialogOptions;

	std::string getText();
	std::shared_ptr<Dialog> getNextDialog(std::shared_ptr<DialogOption> &dialogOption);

	Dialog(std::vector<std::shared_ptr<DialogOption>> &dialogOptions) : dialogOptions(dialogOptions){};
};

class DialogNoResponse : public Dialog{
	class OptionNoResponse : public DialogOption{
	public:
		OptionNoResponse(std::shared_ptr<DynamicObject> &owner) : DialogOption("No response from " + owner->name + ".\n\n", DIALOG_OPTION_END){};
	};
public:
	DialogNoResponse(std::shared_ptr<DynamicObject> &owner) : Dialog(std::vector<std::shared_ptr<DialogOption>>({
		std::shared_ptr<DialogOption>(new OptionNoResponse(owner))
	})){};
};