#pragma once
#include <memory>

class Area;
class Creature;
class Dialog;
class TradeContainer;
class QuestPhase
{
public:
	bool persistent;
	virtual std::shared_ptr<Area> generateArea() = 0;
	virtual std::shared_ptr<Dialog> const &getDialog(Creature &speaker);
	virtual TradeContainer &getTradeContainer(Creature &trader);

	QuestPhase(bool persistent) : persistent(persistent){};
};