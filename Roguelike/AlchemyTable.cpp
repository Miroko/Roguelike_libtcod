#include "AlchemyTable.h"
#include "Engine.h"

std::shared_ptr<OperatableObject> AlchemyTable::copy(){
	return std::shared_ptr<OperatableObject>(new AlchemyTable(*this));
}