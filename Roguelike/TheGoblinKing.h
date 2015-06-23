#pragma once
#include "Quest.h"

class TheGoblinKing : public Quest{
private:
	static const std::shared_ptr<QuestPhase> VILLAGE;
	static const std::shared_ptr<QuestPhase> FOREST;
	static const std::shared_ptr<QuestPhase> NEAR_CAVE;
	static const std::shared_ptr<QuestPhase> CAVE;

	static bool VILLAGE_STORY_TOLD;

	static std::shared_ptr<TradeContainer> VILLAGE_TRADE_CONTAINER;

	class PhaseVillage : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::nextPhaseCondition();
		PhaseVillage() : QuestPhase(""){};
	};
	class PhaseForest : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::nextPhaseCondition();
		PhaseForest() : QuestPhase(""){};
	};
	class PhaseNearCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::nextPhaseCondition();
		PhaseNearCave() : QuestPhase(""){};
	};
	class PhaseCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::nextPhaseCondition();
		PhaseCave() : QuestPhase(""){};
	};

	class DialogVillagerStory1 : public Dialog{
		class OptionStory : public DialogOption{
		public:
			OptionStory(std::shared_ptr<DynamicObject> &owner) :
				DialogOption(owner->name + " asked me to find valuables that goblins have stolen from village.\n\n",
				             "Tell me where those goblins came from.", owner){};
			std::shared_ptr<Dialog> getNextDialog(std::shared_ptr<DynamicObject> &owner){
				return std::shared_ptr<Dialog>(new DialogVillagerStory2(owner));
			}
		};
	public:
		DialogVillagerStory1(std::shared_ptr<DynamicObject> &owner) : Dialog(std::vector<std::shared_ptr<DialogOption>>({
			std::shared_ptr<DialogOption>(new OptionEnd(owner)),
			std::shared_ptr<DialogOption>(new OptionStory(owner))
		})){};
	};

	class DialogVillagerTrade : public Dialog{
	public:
		DialogVillagerTrade(std::shared_ptr<DynamicObject> &owner) : Dialog(std::vector<std::shared_ptr<DialogOption>>({
			std::shared_ptr<DialogOption>(new OptionEnd(owner)),
			std::shared_ptr<DialogOption>(new OptionTrade(owner))
		})){};
	};

	class DialogVillagerStory2 : public Dialog{
		class OptionWillHelp : public DialogOption{
		public:
			OptionWillHelp(std::shared_ptr<DynamicObject> &owner) :
				DialogOption(owner->name + " told me that goblins came from an nearby cave. I should find that cave and return the stolen valuables.\n\n",
			                 "I will help you.", owner){};
			std::shared_ptr<Dialog> getNextDialog(std::shared_ptr<DynamicObject> &owner){
				return std::shared_ptr<Dialog>(new DialogVillagerTrade(owner));
			}
			void onOptionSelect(){
				VILLAGE_STORY_TOLD = true;
			}
		};
	public:
		DialogVillagerStory2(std::shared_ptr<DynamicObject> &owner) : Dialog(std::vector<std::shared_ptr<DialogOption>>({
			std::shared_ptr<DialogOption>(new OptionEnd(owner)),
			std::shared_ptr<DialogOption>(new OptionWillHelp(owner))
		})){};
	};

public:
	std::shared_ptr<QuestPhase> Quest::getNextPhase();
	std::shared_ptr<QuestPhase> Quest::getVillage();
	std::shared_ptr<Dialog> getDialog(std::shared_ptr<DynamicObject> &owner);
	std::shared_ptr<TradeContainer> getTradeContainer(std::shared_ptr<DynamicObject> &owner);

	TheGoblinKing();
};