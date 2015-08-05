#include "Scroll.h"

int Scroll::getValue(){
	return value;
}
std::string Scroll::getStatistics(){
	return Item::getStatistics();
}
void Scroll::onConsume(Creature &consumer){
	
}