#include "String.h"
#include "DynamicObject.h"
#include "Creature.h"
#include <sstream>
#include <iomanip>

std::string String::outOf(int current, int max){
	return "(" + std::to_string(current) + "/" + std::to_string(max) + ")";
}

std::string String::weightKg(double weightKg, bool kg, int precision, bool showPos){
	std::stringstream stream;
	stream.precision(precision);
	if (showPos) stream << std::showpos;
	stream << std::fixed << weightKg;
	if (kg){
		return stream.str() + "kg";
	}
	else return stream.str();
}

std::string String::percentageValue(double percentageValue){
	double realPercentage = percentageValue * 100;
	std::stringstream stream;
	stream.precision(0);
	stream << std::fixed << std::showpos << realPercentage;
	return stream.str() + "%%";
}

std::string String::value(int value){
	std::stringstream stream;
	stream << std::showpos << value;
	return stream.str();
}

std::string String::currency(int amount){
	return std::to_string(amount) + "coins";
}

std::string String::multiplier(double multiplier){
	return "x" + weightKg(multiplier, false);
}

std::string String::damage(int damage){
	return std::to_string(damage) + "dm";
}

std::string String::range(int range){
	return std::to_string(range) + "r";
}

std::string String::defence(int defence){
	return std::to_string(defence) + "a";
}

std::string String::potency(double potency){
	return percentageValue(potency) + "p";
}

std::string String::concentration(double concentration){
	return percentageValue(concentration) + "c";
}

std::string String::duration(int duration){
	return std::to_string(duration) + "t";
}

std::string String::magic(int magic){
	return std::to_string(magic) + "m";
}

std::string String::spellPower(double spellPower){
	return percentageValue(spellPower) + "sp";
}

std::string String::durability(int current, int max){
	return outOf(current, max) + "dr";
}

std::string String::targetName(Creature &creature, DynamicObject &target){
	if (&creature == &target) return "Self";
	else return target.name;
}

std::string String::loremIpsum(){
	return
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. In id maximus urna, eget dignissim nulla."
		"Cras sem ipsum, tincidunt ac euismod vitae, viverra at tellus. Duis in varius ligula. Ut pellentesque"
		"lectus nibh, ut euismod nisl vulputate in. Sed eu ipsum elit. Aenean ut libero nec ligula mattis rutrum"
		"et vitae quam. Nunc ac diam bibendum, gravida dolor in, commodo justo. Duis eu purus at quam sollicitudin"
		"pretium eu nec purus.\n"
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.In id maximus urna, eget dignissim nulla."
		"Cras sem ipsum, tincidunt ac euismod vitae, viverra at tellus. Duis in varius ligula. Ut pellentesque"
		"lectus nibh, ut euismod nisl vulputate in. Sed eu ipsum elit. Aenean ut libero nec ligula mattis rutrum"
		"et vitae quam. Nunc ac diam bibendum, gravida dolor in, commodo justo. Duis eu purus at quam sollicitudin"
		"pretium eu nec purus.\n"
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.In id maximus urna, eget dignissim nulla."
		"Cras sem ipsum, tincidunt ac euismod vitae, viverra at tellus. Duis in varius ligula. Ut pellentesque"
		"lectus nibh, ut euismod nisl vulputate in. Sed eu ipsum elit. Aenean ut libero nec ligula mattis rutrum"
		"et vitae quam. Nunc ac diam bibendum, gravida dolor in, commodo justo. Duis eu purus at quam sollicitudin"
		"pretium eu nec purus.\n"
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.In id maximus urna, eget dignissim nulla."
		"Cras sem ipsum, tincidunt ac euismod vitae, viverra at tellus. Duis in varius ligula. Ut pellentesque"
		"lectus nibh, ut euismod nisl vulputate in. Sed eu ipsum elit. Aenean ut libero nec ligula mattis rutrum"
		"et vitae quam. Nunc ac diam bibendum, gravida dolor in, commodo justo. Duis eu purus at quam sollicitudin"
		"pretium eu nec purus.\n"
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.In id maximus urna, eget dignissim nulla."
		"Cras sem ipsum, tincidunt ac euismod vitae, viverra at tellus. Duis in varius ligula. Ut pellentesque"
		"lectus nibh, ut euismod nisl vulputate in. Sed eu ipsum elit. Aenean ut libero nec ligula mattis rutrum"
		"et vitae quam. Nunc ac diam bibendum, gravida dolor in, commodo justo. Duis eu purus at quam sollicitudin"
		"pretium eu nec purus.\n"
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.In id maximus urna, eget dignissim nulla."
		"Cras sem ipsum, tincidunt ac euismod vitae, viverra at tellus. Duis in varius ligula. Ut pellentesque"
		"lectus nibh, ut euismod nisl vulputate in. Sed eu ipsum elit. Aenean ut libero nec ligula mattis rutrum"
		"et vitae quam. Nunc ac diam bibendum, gravida dolor in, commodo justo. Duis eu purus at quam sollicitudin"
		"pretium eu nec purus.\n";
}