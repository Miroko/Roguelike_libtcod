#include "MagicAction.h"
#include "Accessory.h"
#include "DynamicObject.h"
#include "Creature.h"
#include "Engine.h"
#include <algorithm>

int MagicAction::getMagicCost(Creature &user){
	return (int)(engine::magicCostBase * magicCostModifier);
}

int MagicAction::getStaminaCost(Creature &user){
	return (int)((getMagicCost(user) * engine::magicStaminaCostPerMagic * staminaCostModifier));
}

bool MagicAction::execute(Creature &executer, double actionProficiency, GameObject &actionObject, DynamicObject &target){
	//magic
	if (getMagicCost(executer) > executer.getMagicCurrent()){
		engine::gui.log.addMessage(executer.name + " is too drained of magic to cast " + logDescription + ".");
		return false;
	}

	//stamina
	if (getStaminaCost(executer) > executer.getStaminaCurrent()){
		engine::gui.log.addMessage(executer.name + " is too exhausted to cast " + logDescription + ".");
		return false;
	}
	executer.magicHit(getMagicCost(executer));
	executer.staminaHit(getStaminaCost(executer));

	//cast
	if (engine::random.chancePercentage(actionProficiency)) {
		engine::gui.log.addMessage(executer.name + " casts " + logDescription + " to " + engine::string.targetName(executer, target) + ". ");
	}
	else{
		engine::gui.log.addMessage(executer.name + " fails to cast " + logDescription + ". ");
		return true;
	}

	//visual effect
	CreatureAction::execute(executer, profiencyModifier, actionObject, target);

	//add effects to target
	if (target.isCreature()){
		Creature &targetCreature = static_cast<Creature&>(target);
		for (auto &effect : effects){
			auto clonedEffect = effect->clone();
			clonedEffect->modifier = clonedEffect->modifier * executer.getSpellPowerModifier() * actionProficiency;
			clonedEffect->duration = std::max((int)(clonedEffect->duration * executer.getSpellPowerModifier() * actionProficiency), 1);
			targetCreature.addEffect(clonedEffect);
			if (effect->modifier < 0){
				//negative effect
				targetCreature.ai->onTakeDamage(executer);
			}
		}
	}
	return true;
}

void MagicAction::renderToFrame(GuiFrame &frame, Rectangle &renderBounds){
	//description
	int offsetY = 0;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		getDescription());
	//modifiers
	offsetY += 2;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		"Skill requirement: " + engine::string.percentageValue(profiencyModifier));
	offsetY += 1;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		"Magic cost: " + std::to_string(getMagicCost(*engine::playerHandler.getPlayerCreature())));
	offsetY += 1;
	frame.printString(
		renderBounds.start.x, renderBounds.start.y + offsetY,
		renderBounds.getWidth(), 0,
		Gui::FRAME_FG,
		TCOD_CENTER,
		"Stamina cost: " + std::to_string(getStaminaCost(*engine::playerHandler.getPlayerCreature())));
	//effects
	offsetY += 1;
	for (auto &effect : effects){
		offsetY += 1;
		frame.printString(
			renderBounds.start.x, renderBounds.start.y + offsetY,
			renderBounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_CENTER,
			effect->name + ": " + effect->getDescription());
	}
}

