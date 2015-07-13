#pragma once
#include "Quest.h"
#include "QuestPhase.h"
#include "AreaDrop.h"
#include "AreaHouse.h"
#include "Village.h"
#include "Forest.h"
#include "Cave.h"

class QuestTheGoblinKing : public Quest
{
private:
	class PhaseVillage : public QuestPhase{
	public:
		class VillageMain : public Village{
		public:
			//basic house
			AreaDrop basicHouseResidents = AreaDrop({
				std::make_pair("human_man_villager", std::make_pair("rarity_common", 0.6f)),
				std::make_pair("human_woman_villager", std::make_pair("rarity_common", 0.5f)),
				std::make_pair("human_child_villager", std::make_pair("rarity_common", 0.3f)),
				std::make_pair("human_child_villager", std::make_pair("rarity_common", 0.2f)) });
			AreaHouse houseBasic = AreaHouse(
				"tile_house_wood_wall",
				"tile_house_wood_floor",
				"operatable_door_wooden",
				basicHouseResidents, {
					std::make_pair("operatable_bed_wooden", 1.0f),
					std::make_pair("operatable_bed_wooden", 0.6f),
					std::make_pair("operatable_bed_wooden", 0.3f) });

			//blacksmith
			AreaDrop blacksmithHouseResididents = AreaDrop({
				std::make_pair("human_blacksmith", std::make_pair("rarity_common", 1.0f)),
				std::make_pair("human_blacksmith", std::make_pair("rarity_common", 0.2f)) });
			AreaHouse houseBlacksmith = AreaHouse(
				"tile_house_stone_wall",
				"tile_house_wood_floor",
				"operatable_door_wooden",
				blacksmithHouseResididents, {
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
					std::make_pair(&houseBasic, 0.70f) }){};

		};
		class DialogBlacksmith : public Dialog{
		public:
			std::string getText();

			DialogBlacksmith() : Dialog(std::vector<std::shared_ptr<DialogOption>>({
				DialogOption::END,
				DialogOption::TRADE
			})){};
		};
		std::shared_ptr<Dialog> dialogBlacksmith;
		TradeContainer blacksmithTradeContainer;

		std::shared_ptr<Area> QuestPhase::generateArea();
		std::shared_ptr<Dialog> const &getDialog(Creature &owner);
		TradeContainer &getTradeContainer(Creature &speaker);
		PhaseVillage() : QuestPhase(), blacksmithTradeContainer(TradeContainer(100, ItemContainer())){
			dialogBlacksmith = std::shared_ptr<Dialog>(new DialogBlacksmith());
		};
	};
	class PhaseWayThroughForest : public QuestPhase{
	public:
		class ForestGoblin : public Forest{
		public:
			AreaDrop dropGoblin = AreaDrop({
				std::make_pair("goblin_dagger_low", std::make_pair("rarity_common", 1.0f)),
				std::make_pair("goblin_dagger_low", std::make_pair("rarity_common", 1.0f)),
				std::make_pair("goblin_dagger_low", std::make_pair("rarity_common", 0.1f)) });
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

		std::shared_ptr<Area> QuestPhase::generateArea();
		std::shared_ptr<Dialog> const &getDialog(Creature &owner);
		TradeContainer &getTradeContainer(Creature &trader);
		PhaseWayThroughForest() : QuestPhase(){};
	};
	class PhaseInCave : public QuestPhase{
	public:
		class CaveGoblin : public Cave{
		public:
			AreaDrop dropGoblin = AreaDrop({
				std::make_pair("goblin_dagger_low", std::make_pair("rarity_common", 1.0f)),
				std::make_pair("goblin_dagger_medium", std::make_pair("rarity_uncommon", 0.8f)),
				std::make_pair("goblin_dagger_low", std::make_pair("rarity_common", 0.1f)),
				std::make_pair("goblin_dagger_low", std::make_pair("rarity_common", 0.1f)) });

			CaveGoblin() : Cave(
				"tile_cave_wall1",
				"tile_cave_wall2",
				"tile_cave_floor1",
				"tile_cave_floor2",
				"tile_cave_water",
				"tile_cave_portal",
				"tile_cave_rotten_wall",
				dropGoblin,
				200, 0.6f, 1, 0.02f, 0.02f, 2, 0.3f, 12){};
		};

		std::shared_ptr<Area> QuestPhase::generateArea();
		std::shared_ptr<Dialog> const &getDialog(Creature &owner);
		TradeContainer &getTradeContainer(Creature &trader);
		PhaseInCave() : QuestPhase(){};
	};

public:
	QuestTheGoblinKing() : Quest("The Goblin King",
	{
		std::shared_ptr<QuestPhase>(new PhaseVillage()),
		std::shared_ptr<QuestPhase>(new PhaseWayThroughForest()),
		std::shared_ptr<QuestPhase>(new PhaseInCave())
	}){};
};

