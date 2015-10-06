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
				std::make_pair("villager_man", std::make_pair("common", 0.6)),
				std::make_pair("villager_woman", std::make_pair("common", 0.5)),
				std::make_pair("villager_child", std::make_pair("common", 0.3)),
				std::make_pair("villager_child", std::make_pair("common", 0.2))
			});
			AreaHouse houseBasic = AreaHouse(
				"house_wall_wood",
				"house_floor_wood",
				"door_wood",
				basicHouseResidents,
				{ std::make_pair("bed_wood", 1.0),
				  std::make_pair("bed_wood", 0.6),
				  std::make_pair("bed_wood", 0.3) });

			//blacksmith
			AreaDrop blacksmithHouseResididents = AreaDrop({
				std::make_pair("villager_blacksmith", std::make_pair("common", 1.0)),
				std::make_pair("villager_blacksmith", std::make_pair("common", 0.2)) 
			});
			AreaHouse houseBlacksmith = AreaHouse(
				"house_wall_stone",
				"house_floor_wood",
				"door_wood",
				blacksmithHouseResididents,
				{ std::make_pair("forge", 1.0),
				  std::make_pair("forge", 0.6),
				  std::make_pair("anvil", 1.0),
				  std::make_pair("anvil", 0.6),
				  std::make_pair("anvil", 0.3) });

			//alchemist
			AreaDrop alchemistHouseResididents = AreaDrop({
				std::make_pair("villager_alchemist", std::make_pair("common", 1.0)),
				std::make_pair("villager_alchemist", std::make_pair("common", 0.2))
			});
			AreaHouse houseAlchemist = AreaHouse(
				"house_wall_stone",
				"house_floor_wood",
				"door_wood",
				alchemistHouseResididents,
				{ std::make_pair("alchemy_table1", 1.0),
				  std::make_pair("alchemy_table2", 1.0),
				  std::make_pair("alchemy_table1", 0.6),
				  std::make_pair("alchemy_table2", 0.6),
				  std::make_pair("alchemy_table1", 0.3) });

			VillageMain() : Village(
				"forest_floor_grass",
				"forest_wall_tree",
				"forest_wall_stone",
				"forest_floor_stone",
				"path_sand",
				150,
				{ std::make_pair(&houseBlacksmith, 0.70),
				  std::make_pair(&houseAlchemist, 0.70),
				  std::make_pair(&houseBasic, 1.00) }){};

		};
		//dialogs
		class DialogBlacksmith : public Dialog{
		public:
			std::string getText();

			DialogBlacksmith() : Dialog(std::vector<std::shared_ptr<DialogOption>>({
				DialogOption::END,
				DialogOption::TRADE
			})){};
		};
		std::shared_ptr<Dialog> dialogBlacksmith;

		class DialogAlchemist : public Dialog{
		public:
			std::string getText();

			DialogAlchemist() : Dialog(std::vector<std::shared_ptr<DialogOption>>({
				DialogOption::END,
				DialogOption::TRADE
			})){};
		};
		std::shared_ptr<Dialog> dialogAlchemist;

		//trade containers
		TradeContainer blacksmithTradeContainer;
		TradeContainer alchemistTradeContainer;

		std::shared_ptr<Area> QuestPhase::generateArea();
		std::shared_ptr<Dialog> const &getDialog(Creature &owner);
		TradeContainer &getTradeContainer(Creature &speaker);
		PhaseVillage() : QuestPhase(true),
			dialogBlacksmith(std::shared_ptr<Dialog>(new DialogBlacksmith())),
			dialogAlchemist(std::shared_ptr<Dialog>(new DialogAlchemist())),
			blacksmithTradeContainer(TradeContainer(3000, 25, 25, 0, 0)),
			alchemistTradeContainer(TradeContainer(2000, 0, 0, 25, 40)){};
	};
	class PhaseWayThroughForest : public QuestPhase{
	public:
		class ForestGoblin : public Forest{
		public:
			AreaDrop dropGoblin = AreaDrop(
			{
				std::make_pair("goblin_melee", std::make_pair("common", 0.8)),
				std::make_pair("goblin_melee", std::make_pair("common", 0.6)),
				std::make_pair("goblin_melee", std::make_pair("common", 0.4)),
				std::make_pair("goblin_ranged", std::make_pair("common", 0.4)),
				std::make_pair("goblin_magic", std::make_pair("common", 0.3)) 
			},
			{	
				std::make_pair("chest_wood_small", std::make_pair("uncommon", 0.8)) 
			});

			ForestGoblin() : Forest(
				"forest_floor_grass",
				"forest_wall_tree",
				"forest_wall_stone",
				"forest_floor_stone",
				"forest_portal",
				dropGoblin,
				100, 0.6, 0.02, 22
				){};
		};

		std::shared_ptr<Area> QuestPhase::generateArea();
		PhaseWayThroughForest() : QuestPhase(false){};
	};
	class PhaseInCave : public QuestPhase{
	public:
		class CaveGoblin : public Cave{
		public:
			AreaDrop dropGoblin = AreaDrop(
			{
				std::make_pair("goblin_melee", std::make_pair("common", 0.8)),
				std::make_pair("goblin_ranged", std::make_pair("common", 0.6)),
				std::make_pair("goblin_melee", std::make_pair("uncommon", 0.3)),
				std::make_pair("goblin_ranged", std::make_pair("uncommon", 0.2)),
				std::make_pair("goblin_magic", std::make_pair("rare", 0.1))
			},
			{
				std::make_pair("barrel_wood", std::make_pair("common", 1.0)),
				std::make_pair("barrel_wood", std::make_pair("common", 1.0)),
				std::make_pair("barrel_wood", std::make_pair("common", 1.0)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("chest_wood_large", std::make_pair("rare", 0.2)),
			});

			CaveGoblin() : Cave(
				"cave_wall_stone1",
				"cave_wall_stone2",
				"cave_floor_stone1",
				"cave_floor_stone2",
				"cave_water",
				"cave_portal",
				"cave_wall_wood",
				dropGoblin,
				200, 0.6, 1, 0.02, 0.02, 3, 0.3, 12
				){};
		};

		std::shared_ptr<Area> QuestPhase::generateArea();
		PhaseInCave() : QuestPhase(false){};
	};
	class PhaseKing : public QuestPhase{
	public:
		class CaveKing : public Cave{
		public:
			AreaDrop dropGoblin = AreaDrop({
				std::make_pair("goblin_melee", std::make_pair("uncommon", 1.0)),
				std::make_pair("goblin_melee", std::make_pair("uncommon", 1.0)), 
				std::make_pair("goblin_ranged", std::make_pair("uncommon", 0.5)),
			},
			{
				std::make_pair("barrel_wood", std::make_pair("common", 1.0)),
				std::make_pair("barrel_wood", std::make_pair("common", 1.0)),
				std::make_pair("barrel_wood", std::make_pair("common", 1.0)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("chest_wood_large", std::make_pair("rare", 0.2)),
			});

			AreaDrop dropKing = AreaDrop(
			{
				std::make_pair("goblin_king", std::make_pair("unique", 1.0)),
				std::make_pair("goblin_ranged", std::make_pair("epic", 1.0))
			},
			{
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("barrel_wood", std::make_pair("common", 0.8)),
				std::make_pair("chest_wood_large", std::make_pair("epic", 0.5)),
				std::make_pair("chest_wood_large", std::make_pair("epic", 0.5)),
			});

			CaveKing() : Cave(
				"cave_wall_stone1",
				"cave_wall_stone2",
				"cave_floor_stone1",
				"cave_floor_stone2",
				"cave_water",
				"cave_portal",
				"cave_wall_wood",
				dropGoblin,
				150, 0.4, 2, 0.02, 0.02, 3, 0.3, 12
				){};
		};

		std::shared_ptr<Area> QuestPhase::generateArea();
		PhaseKing() : QuestPhase(true){};
	};

public:
	QuestTheGoblinKing() : Quest("The Goblin King",
	{
		std::shared_ptr<QuestPhase>(new PhaseVillage()),
		std::shared_ptr<QuestPhase>(new PhaseWayThroughForest()),
		std::shared_ptr<QuestPhase>(new PhaseInCave()),
		std::shared_ptr<QuestPhase>(new PhaseKing())
	}){};
};

