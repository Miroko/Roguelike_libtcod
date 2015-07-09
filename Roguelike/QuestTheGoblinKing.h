#pragma once
#include "Quest.h"
#include "QuestPhase.h"
#include "AreaDrop.h"
#include "AreaHouse.h"
#include "Village.h"
#include "Forest.h"

class QuestTheGoblinKing : public Quest
{
private:
	class VillageMain : public Village{
	public:
		AreaDrop basicHouseResidents = AreaDrop(
		{
			std::make_pair("human_man_villager", std::make_pair("rarity_common", 0.6f)),
			std::make_pair("human_woman_villager", std::make_pair("rarity_common", 0.5f)),
			std::make_pair("human_child_villager", std::make_pair("rarity_common", 0.3f)),
			std::make_pair("human_child_villager", std::make_pair("rarity_common", 0.2f))
		});
		AreaHouse houseBasic = AreaHouse(
			"tile_house_wood_wall",
			"tile_house_wood_floor",
			"operatable_door_wooden",
			basicHouseResidents,{
			std::make_pair("operatable_bed_wooden", 1.0f),
			std::make_pair("operatable_bed_wooden", 0.6f),
			std::make_pair("operatable_bed_wooden", 0.3f) });

		AreaDrop blacksmithHouseResididents = AreaDrop(
		{
			std::make_pair("human_blacksmith", std::make_pair("rarity_common", 1.0f)),
			std::make_pair("human_blacksmith", std::make_pair("rarity_common", 0.2f))
		});
		AreaHouse houseBlacksmith = AreaHouse(
			"tile_house_stone_wall",
			"tile_house_wood_floor",
			"operatable_door_wooden",
			blacksmithHouseResididents,	{
			std::make_pair("operatable_forge", 1.0f), 
			std::make_pair("operatable_forge", 0.6f),
			std::make_pair("operatable_anvil", 1.0f),
			std::make_pair("operatable_anvil", 0.6f),
			std::make_pair("operatable_anvil", 0.3f) });

		VillageMain() : Village(
			"tile_forest_grass",
			"tile_forest_tree",
			"tile_nature_stone_wall",
			"tile_nature_stone_floor",
			"tile_path_sand",
			150, {
			std::make_pair(&houseBlacksmith, 0.50f),
			std::make_pair(&houseBasic, 0.70f) } ){};

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
		"tile_forest_grass",
		"tile_forest_tree",
		"tile_nature_stone_wall",
		"tile_nature_stone_floor",
		"tile_forest_portal",
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

