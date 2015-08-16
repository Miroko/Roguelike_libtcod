#pragma once
#include "GuiFrame.h"
#include "Dialog.h"

class DialogFrame : public GuiFrame
{
private:
	std::shared_ptr<Dialog> currentDialog;
	int selectedOption;
public:
	void setDialog(std::shared_ptr<Dialog> dialog);

	bool handleKey(TCOD_key_t key);
	void GuiFrame::render();

	DialogFrame(char controlKey, bool open, double alphaFg, double alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Dialog"){};
};

