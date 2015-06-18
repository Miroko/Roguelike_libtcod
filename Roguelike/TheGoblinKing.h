#pragma once
#include "Quest.h"

class TheGoblinKing : public Quest{
private:
	class WayToCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		WayToCave() : QuestPhase(""){};
	};
	class CaveEntrance : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		CaveEntrance() : QuestPhase(""){};
	};
	class InTheCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		InTheCave() : QuestPhase(""){};
	};
	class InVillage : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		InVillage() : QuestPhase(""){};
	};

	static bool storyTold;

	class DialogVillagerStory1 : public Dialog{
		class OptionStory : public DialogOption{
		public:
			OptionStory(std::shared_ptr<DynamicObject> &owner) : DialogOption(owner->name + " asked me to find valuables that goblins have stolen from village.\n\n",
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

	class DialogVillagerStory2 : public Dialog{
		class OptionWillHelp : public DialogOption{
		public:
			OptionWillHelp(std::shared_ptr<DynamicObject> &owner) : DialogOption(owner->name + " told me that goblins came from an nearby cave. I should find that cave and return the stolen valuables.\n\n",
			                                                                  "I will help you.", owner){};
			std::shared_ptr<Dialog> getNextDialog(std::shared_ptr<DynamicObject> &owner){
				return std::shared_ptr<Dialog>(new DialogVillagerTrade(owner));
			}
			void onOptionSelect(){
				storyTold = true;
			}
		};
	public:
		DialogVillagerStory2(std::shared_ptr<DynamicObject> &owner) : Dialog(std::vector<std::shared_ptr<DialogOption>>({
			std::shared_ptr<DialogOption>(new OptionEnd(owner)),
			std::shared_ptr<DialogOption>(new OptionWillHelp(owner))
		})){};
	};

	class DialogVillagerTrade : public Dialog{
	public:
		DialogVillagerTrade(std::shared_ptr<DynamicObject> &owner) : Dialog(std::vector<std::shared_ptr<DialogOption>>({
			std::shared_ptr<DialogOption>(new OptionEnd(owner)),
			std::shared_ptr<DialogOption>(new OptionTrade(owner))
		})){};
	};

public:
	std::shared_ptr<QuestPhase> Quest::getNextPhase();
	std::shared_ptr<QuestPhase> Quest::getVillage();
	std::shared_ptr<Dialog> getDialog(std::shared_ptr<DynamicObject> &owner);

	TheGoblinKing() : Quest("The Goblin King"){}
};