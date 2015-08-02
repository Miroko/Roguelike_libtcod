#pragma once
#include "GuiFrame.h"
#include "DynamicObject.h"
#include "GuiGameObjectDisplay.h"
#include <vector>
#include <memory>

class AttackFrame : public GuiFrame
{
private:
	const TCODColor cursorColor = TCODColor::green;
	std::vector<std::shared_ptr<DynamicObject>> attackableObjects;
	std::shared_ptr<DynamicObject> previouslyAttacked;
	int selectedObjectIndex;

	Rectangle guiGameObjectDisplayBounds;
	GuiGameObjectDisplay guiGameObjectDisplay;

public:
	void updateTarget();
	void updateAttackableObjects();
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);
	void update();
	void onOpen();
	void init(Rectangle &bounds);

	AttackFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg){};
};

