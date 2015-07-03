#include "QuestPhase.h"
#include "Dialog.h"
#include "Engine.h"

std::shared_ptr<Dialog> const &QuestPhase::getDialog(DynamicObject &speaker){
	Dialog::NO_RESPONSE->setSpeaker(speaker);
	return Dialog::NO_RESPONSE;
}
