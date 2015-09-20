#include "SkillFrame.h"
#include "Engine.h"
#include "String.h"
#include "CreatureSkill.h"

void SkillFrame::onOpen(){
	setSkillsAndProfiencies(engine::playerHandler.getPlayerCreature()->getCombatSkillsAndProficiencies());
}

bool SkillFrame::handleKey(TCOD_key_t &key){
	bool handled = false;
	if (!isOpen){
		handled = GuiFrame::handleKey(key);
	}
	else{
		handled = selectableSkillList.handleKey(key);
		if (!handled){
			close();
			handled = true;
		}
	}
	return handled;
}

void SkillFrame::render(){
	GuiFrame::render();
	displayBox.renderTo(*this, displayBoxBounds);
	selectableSkillList.renderTo(*this, selectableSkillListBounds);
	if (selectedSkill) selectedSkill->renderToFrame(*this, skillDisplayBounds);
	blit();
}

void SkillFrame::init(Rectangle bounds){
	GuiFrame::init(bounds);
	displayBoxBounds= Rectangle(Point2D(0, 3), Point2D(bounds.getWidth(), 14));
	skillDisplayBounds = Rectangle(Point2D(0, 3), Point2D(getWidth(), 14));
	selectableSkillListBounds = Rectangle(Point2D(0, 14), Point2D(getWidth(), getHeight()));
	selectableSkillList.setGetOperationsFunction(
		[this](CreatureSkill *skill, bool selected) -> std::vector<std::string>{
		if (selected){
			//update item in display
			selectedSkill = skill;
			return SKILL_OPERATIONS;
		}
		else return{ "" };
	});
	selectableSkillList.setOnOperationSelectedFunction(
		[this](CreatureSkill *skill, double profiency, std::string operation){
		if (operation == USE){
			if (skill->isType(CreatureSkill::MAGIC)){
				engine::gui.action.setActionsAndProfiencies(*skill, skill->getActionsAndProficiencies(profiency));
				engine::gui.action.open();
				close();
			}
			else if (skill->isType(CreatureSkill::WEAPON)){
				engine::gui.attack.setSkillAndAction(*skill, *skill->actions.at(0));
				engine::gui.attack.open();
				close();
			}
		}
	});
}

void SkillFrame::setSkillsAndProfiencies(std::vector<std::pair<CreatureSkill*, double>> skillsAndProfiencies){
	selectableSkillList.setSkillsAndProfiencies(skillsAndProfiencies);
}
