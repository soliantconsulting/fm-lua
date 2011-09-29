#include <vector>
#include "bstring/bstrlib.h"
#include "bstring/bstrwrap.h"
#pragma once

struct CustomFunc
{
	char* luacode;
	CBStringList paramaters;
};

struct CustomFunctions
{
	static std::vector<CustomFunc> functions;
	//static std::vector<std::vector<char*>> functionPrototype;
	static const int indexOffSet = 50;
	//static int apples;
};
