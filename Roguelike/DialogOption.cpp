#include "DialogOption.h"

void DialogOption::onOptionSelect(){

}

std::shared_ptr<Dialog> DialogOption::getNextDialog(std::shared_ptr<DynamicObject> &owner){
	return DIALOG_END;
}
