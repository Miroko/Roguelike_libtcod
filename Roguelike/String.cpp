#include "String.h"

std::string String::outOf(int current, int max){
	return "(" + std::to_string(current) + "/" + std::to_string(max) + ")";
}

std::string String::weight(float weight, bool kg, int precision){
	std::string value = std::to_string(weight);
	value = value.substr(0, precision + value.size() - 6);
	if (kg) value += "kg";
	return value;
}

std::string String::currency(int amount){
	return std::to_string(amount) + "c";
}

std::string String::multiplier(float multiplier){
	return "x" + weight(multiplier, false);
}

std::string String::damage(int damage){
	return std::to_string(damage) + "d";
}

std::string String::range(int range){
	return std::to_string(range) + "r";
}

std::string String::defence(int defence){
	return std::to_string(defence) + "a";
}

std::string String::duration(int duration){
	return std::to_string(duration) + "t";
}

std::string String::percentage(float percentage){
	return weight(percentage, false) + "%%";
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