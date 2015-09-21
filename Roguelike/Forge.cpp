#include "Forge.h"

std::shared_ptr<OperatableObject> Forge::copy(){
	return std::shared_ptr<OperatableObject>(new Forge(*this));
}