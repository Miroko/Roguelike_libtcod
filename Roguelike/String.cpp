#include "String.h"

std::string String::outOf(int current, int max){
	return "(" + std::to_string(current) + "/" + std::to_string(max) + ")";
}

std::string String::weight(float weight, bool kg, int precision){
	int rounded = (int)weight;
	int decimals = (int)pow(10, precision);
	int decimalPart = (int)(weight * decimals - rounded * decimals);
	std::string value = std::to_string(rounded) + "." + std::to_string(decimalPart);
	if (kg) value += "kg";
	return value;
}

std::string String::currency(int currency){
	return std::to_string(currency) + "c";
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