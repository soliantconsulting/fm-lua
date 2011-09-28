#include <vector>

#pragma once

struct CustomFunc
{
	char* luacode;
	std::vector<const char *> paramaters;
};

struct CustomFunctions
{
	static std::vector<CustomFunc> functions;
	//static std::vector<std::vector<char*>> functionPrototype;
	static const int indexOffSet = 50;
	//static int apples;
};
