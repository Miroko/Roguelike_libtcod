#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject
{

private:

public:

	enum Size
	{
		SMALL,
		MEDIUM,
		LARGE
	};

	Point2D location;
	
	Size size;
	
	virtual bool isBlockedBy(DynamicObject &object) = 0; 

	void update(float elapsed);

	DynamicObject(Glyph glyph, std::string name, Size size, Point2D location) : GameObject(glyph, name), size(size), location(location) {};
	DynamicObject(){}
};

class Human : public DynamicObject
{
public:
	bool DynamicObject::isBlockedBy(DynamicObject &object);

	Human(std::string name, Point2D location) : DynamicObject(Glyph(TCODColor::lighterAmber, '@'), name, MEDIUM, location){};
	Human();
};
