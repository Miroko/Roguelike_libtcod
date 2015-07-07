#pragma once
#include "Quest.h"
#include "QuestPhase.h"
#include "AreaDrop.h"
#include "Village.h"
#include "Forest.h"

class QuestTheGoblinKing : public Quest
{
private:
	class VillageMain : public Village{
	public:
		AreaDrop houseResidents = AreaDrop(
		{
			std::make_pair("human_man_villager", std::make_pair("rarity_common", 1.0f)),
			std::make_pair("human_woman_villager", std::make_pair("rarity_common", 0.9f)),
			std::make_pair("human_child_villager", std::make_pair("rarity_common", 0.3f)),
			std::make_pair("human_child_villager", std::make_pair("rarity_common", 0.1f))
		});

		VillageMain() : Village(
			"forest_floor",
			"forest_wall",
			"wood_wall",
			"wood_floor",
			"sand_path",
			"door_wooden",
			100, 
			houseResidents){};

	};
	class ForestGoblin : public Forest{
	public:
		AreaDrop dropGoblin = AreaDrop(
		{
			std::make_pair("goblin_dagger", std::make_pair("rarity_common", 1.0f)),
			std::make_pair("goblin_dagger", std::make_pair("rarity_uncommon", 0.5f)),
			std::make_pair("goblin_dagger", std::make_pair("rarity_common", 0.3f)),
			std::make_pair("goblin_dagger", std::make_pair("rarity_common", 0.3f))
		});

		ForestGoblin() : Forest(
		"forest_floor",
		"forest_wall",
		"stone_wall",
		"stone_floor",
		"forest_portal",
		100, 0.6f, 0.02f, 8){};

		void onGatePlace(Point2D &location);
		void onStonePlaced(Point2D &location);

	};
	class PhaseVillage : public QuestPhase
	{
	public:
		std::shared_ptr<Area> QuestPhase::generateArea();
		std::shared_ptr<Dialog> const &QuestPhase::getDialog(DynamicObject &owner);
		std::shared_ptr<TradeContainer> const &QuestPhase::getTradeContainer(DynamicObject &speaker);
		PhaseVillage() : QuestPhase(){};
	};
	class PhaseWayThroughForest : public QuestPhase
	{
	public:
		std::shared_ptr<Area> QuestPhase::generateArea();
		std::shared_ptr<Dialog> const &QuestPhase::getDialog(DynamicObject &owner);
		std::shared_ptr<TradeContainer> const &QuestPhase::getTradeContainer(DynamicObject &trader);
		PhaseWayThroughForest() : QuestPhase(){};
	};

public:
	QuestTheGoblinKing() : Quest("The Goblin King",
	{
		std::shared_ptr<QuestPhase>(new PhaseVillage()),
		std::shared_ptr<QuestPhase>(new PhaseWayThroughForest())
	}){};
};

