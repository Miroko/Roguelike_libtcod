#include "DialogOption.h"
#include "Engine.h"
#include "Quest.h"

const std::shared_ptr<DialogOption> DialogOption::END = std::shared_ptr<DialogOption>(new OptionEnd());
const std::shared_ptr<DialogOption> DialogOption::TRADE = std::shared_ptr<DialogOption>(new OptionTrade());

//End
void OptionEnd::onOptionSelect(Creature &speaker){
	//nothing
}
std::string OptionEnd::getText(Creature &speaker){
	return ""; //no text
}
std::string OptionEnd::getOptionText(Creature &speaker){
	return engine::string.DIALOG_OPTION_END;
}
std::shared_ptr<Dialog> const &OptionEnd::getNextDialog(Creature &speaker){
	onOptionSelect(speaker);
	return Dialog::DIALOG_END; //Null pointer checked in dialogFrame for ending the dialog
}

//Trade
void OptionTrade::onOptionSelect(Creature &speaker){
	engine::gui.trade.setContainers(
		engine::playerHandler.getPlayerCreature()->inventory.items,
		engine::questHandler.getCurrentQuest()->getCurrentPhase()->getTradeContainer(speaker));
	engine::gui.trade.open();
}
std::string OptionTrade::getText(Creature &speaker){
	return speaker.name + " is willing to trade. \n\n";
}
std::string OptionTrade::getOptionText(Creature &speaker){
	return engine::string.DIALOG_OPTION_TRADE;
}
std::shared_ptr<Dialog> const &OptionTrade::getNextDialog(Creature &speaker){
	onOptionSelect(speaker);
	return Dialog::DIALOG_END;
}
