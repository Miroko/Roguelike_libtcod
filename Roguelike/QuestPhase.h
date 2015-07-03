#pragma once
#include <memory>

class Area;
class DynamicObject;
class Dialog;
class TradeContainer;
class QuestPhase
{
public:
	virtual std::shared_ptr<Area> generateArea() = 0;
	virtual std::shared_ptr<Dialog> const &getDialog(DynamicObject &speaker) = 0;
	virtual std::shared_ptr<TradeContainer> const &getTradeContainer(DynamicObject &trader) = 0;

	QuestPhase(){};
};