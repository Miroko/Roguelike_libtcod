#include "Quest.h"

std::shared_ptr<Dialog> Quest::getDialog(std::shared_ptr<DynamicObject> &owner){
	return std::shared_ptr<Dialog>(new DialogNoResponse(owner));
}