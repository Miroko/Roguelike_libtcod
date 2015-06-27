#include "String.h"

std::string String::weight(float weight, int precision){
	int rounded = (int)weight;
	int decimals = pow(10, precision);
	int decimalPart = weight * decimals - rounded * decimals;
	return std::to_string(rounded) + "." + std::to_string(decimalPart) + "kg";
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