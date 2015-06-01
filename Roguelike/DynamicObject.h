#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject
{

private:

public:

	//Size
	enum Size
	{
		SMALL,
		MEDIUM,
		LARGE
	};
	Size size;
	virtual bool isBlockedBy(DynamicObject &object);
	//----

	Point2D location;
	
	virtual void update() = 0;

	DynamicObject(Glyph glyph, std::string name, Size size) : GameObject(glyph, name), size(size){};
	DynamicObject(){}
};
