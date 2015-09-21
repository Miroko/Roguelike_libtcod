#include "Anvil.h"
#include "Engine.h"

std::shared_ptr<OperatableObject> Anvil::copy(){
	return std::shared_ptr<OperatableObject>(new Anvil(*this));
}