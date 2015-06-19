#include "DialogOption.h"
#include "Engine.h"

void DialogOption::onOptionSelect(){

}

std::shared_ptr<Dialog> DialogOption::getNextDialog(std::shared_ptr<DynamicObject> &owner){
	return DIALOG_END;
}

void OptionTrade::onOptionSelect(){
	Engine::GUI.trade.setTradeContainer(Engine::questHandler.currentQuest->getTradeContainer(owner));
	Engine::GUI.trade.open();
}
