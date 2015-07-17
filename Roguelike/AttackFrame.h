#pragma once
#include "GuiFrame.h"
#include "DynamicObject.h"
#include <vector>
#include <memory>

class AttackFrame : public GuiFrame
{
private:
	const TCODColor cursorColor = TCODColor::green;
	std::vector<std::shared_ptr<DynamicObject>> attackableObjects;
	std::shared_ptr<DynamicObject> previouslyAttacked;
	int objectIndex;
public:
	Point2D attackLocation;

	void setAttackableObjects(std::vector<std::shared_ptr<DynamicObject>> attackableObjects);
	void updateTarget();
	void GuiFrame::render();
	bool handleKey(TCOD_key_t key);
	void onOpen();
	void onClose();

	AttackFrame(char controlKey, bool open, float alphaFg, float alphaBg) :
		GuiFrame(controlKey, open, alphaFg, alphaBg){};
};

