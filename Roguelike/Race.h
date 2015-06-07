#pragma once
#include <string>
#include <set>
namespace race{
	class Race
	{
	public:
		std::string name;

		Race(std::string name) : name(name){};
	};
}