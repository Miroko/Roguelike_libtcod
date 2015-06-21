#pragma once
#include "DynamicObject.h"
class OperatableObject : public DynamicObject
{
public:
	template <typename T> static std::shared_ptr<T> newOperatable(const std::shared_ptr<T> &operatableObjectTemplate, bool isOn = false){
		std::shared_ptr<T> operatableObject = std::shared_ptr<T>(new T(*operatableObjectTemplate));
		if (isOn) operatableObject->on();
		else operatableObject->off();
		return operatableObject;
	}

	bool isOn;

	Glyph onGlyph;
	Glyph offGlyph;

	virtual void on();
	virtual void off();

	void messageDeath();

	void render(int x, int y);

	OperatableObject(Glyph onGlyph, Glyph offGlyph, std::string name, int health, const LootContainer &loot) :
		DynamicObject(offGlyph, name, LARGE, false, health, loot), onGlyph(onGlyph), offGlyph(offGlyph){};
};
