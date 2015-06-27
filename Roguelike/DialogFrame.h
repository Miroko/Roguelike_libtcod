#pragma once
#include "GuiFrame.h"
#include "Dialog.h"
class DialogFrame : public GuiFrame
{
private:
	TCODColor selectionColor = TCODColor::lightGreen;
	std::shared_ptr<Dialog> currentDialog;
	int selectedOption;
public:
	void setDialog(std::shared_ptr<Dialog> dialog);

	bool handleKey(TCOD_key_t key, bool &requireUpdate);
	void GuiFrame::render();

	DialogFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg, "Dialog"){};
};

