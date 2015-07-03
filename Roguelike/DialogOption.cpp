#include "DialogOption.h"
#include "Engine.h"
#include "Quest.h"

//End
void OptionEnd::onOptionSelect(DynamicObject &speaker){
	//nothing
}
std::string OptionEnd::getText(DynamicObject &speaker){
	return ""; //no text
}
std::string OptionEnd::getOptionText(DynamicObject &speaker){
	return engine::string.DIALOG_OPTION_END;
}
std::shared_ptr<Dialog> const &OptionEnd::getNextDialog(DynamicObject &speaker){
	onOptionSelect(speaker);
	return Dialog::END; //Null pointer checked in dialogFrame for ending the dialog
}

//Trade
void OptionTrade::onOptionSelect(DynamicObject &speaker){
	engine::gui.trade.setContainers(
		engine::playerHandler.getPlayerCreature()->inventory.items,
		*engine::questHandler.getCurrentQuest()->getCurrentPhase()->getTradeContainer(speaker));
	engine::gui.trade.open();
}
std::string OptionTrade::getText(DynamicObject &speaker){
	return speaker.name + " is willing to trade. \n\n";
}
std::string OptionTrade::getOptionText(DynamicObject &speaker){
	return engine::string.DIALOG_OPTION_TRADE;
}
std::shared_ptr<Dialog> const &OptionTrade::getNextDialog(DynamicObject &speaker){
	onOptionSelect(speaker);
	return Dialog::END;
}