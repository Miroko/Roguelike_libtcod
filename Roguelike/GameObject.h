#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "Glyph.h"
#include "GuiObject.h"
#include <string>

class GameObject : public GuiObject
{
public:	
	enum Type{
		FLOOR,
		WALL,
		PORTAL,
		WATER,

		CREATURE,
		
		DOOR,
		BED,
		FORGE,
		ANVIL,
		ALCHEMY_TABLE,

		WEAPON_MELEE,
		WEAPON_RANGED,
		ARMOR_HEAD,
		ARMOR_BODY,
		ARMOR_HAND,
		ARMOR_LEG,
		ACCESSORY_AMULET,
		ACCESSORY_RING,

		CONSUMABLE,
		NONE,
	};
	Type type;
	std::string name;
	Glyph glyph;

	bool isCreature();
	bool isWeapon();
	bool isArmor();
	bool isAccessory();
	bool isEquipment();
	bool isConsumable();
	bool isOperatable();
	bool isTile();
	bool isType(Type type);
		
	virtual void render(int x, int y);

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;
	void GuiObject::renderToFrameLine(GuiFrame &frame, Rectangle &renderBounds, int offsetY) override;
	std::string GuiObject::getStatistics() override;
	std::string GuiObject::getDescription() override;

	GameObject(std::string name, Type type, Glyph glyph) :
		name(name),
		type(type), 
		glyph(glyph){};
};

