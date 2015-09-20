#include "ActionFrame.h"
#include "Engine.h"
#include "String.h"
#include "CreatureAction.h"

bool ActionFrame::handleKey(TCOD_key_t &key){
	bool handled = false;
	if (!isOpen){
		handled = GuiFrame::handleKey(key);
	}
	else{
		handled = selectableActionList.handleKey(key);
		if (!handled){
			close();
			handled = true;
		}
	}
	return handled;
}

void ActionFrame::render(){
	GuiFrame::render();
	displayBox.renderTo(*this, displayBoxBounds);
	selectableActionList.renderTo(*this, selectableActionListBounds);
	if (selectedAction) selectedAction->renderToFrame(*this, skillDisplayBounds);
	blit();
}

void ActionFrame::init(Rectangle bounds){
	GuiFrame::init(bounds);
	displayBoxBounds = Rectangle(Point2D(0, 3), Point2D(bounds.getWidth(), 14));
	skillDisplayBounds = Rectangle(Point2D(0, 3), Point2D(getWidth(), 14));
	selectableActionListBounds= Rectangle(Point2D(0, 14), Point2D(getWidth(), getHeight()));
	selectableActionList.setGetOperationsFunction(
		[this](CreatureAction *action, bool selected) -> std::vector<std::string>{
		if (selected){
			//update item in display
			selectedAction = action;
			return ACTION_OPERATIONS;
		}
		else return{ "" };
	});
	selectableActionList.setOnOperationSelectedFunction(
		[this](CreatureSkill *skill, CreatureAction *action, std::string operation){
		if (operation == USE){
			engine::gui.attack.setSkillAndAction(*skill, *action);
			engine::gui.attack.open();
			close();
		}
	});
}

void ActionFrame::setActionsAndProfiencies(CreatureSkill &selectedSkill, std::vector<std::pair<CreatureAction*, double>> actionsAndProfiencies){
	selectableActionList.setActionsAndProfiencies(selectedSkill, actionsAndProfiencies);
}
