#pragma once
#include "DyckPaths.hpp"
#include <vector>

bool testDyckPaths();

inline bool dyckpathiscorrect(const std::vector<int>& x)
{

	int suma = 0;

	for (auto u : x)
	{
		suma += u;

		if (suma < 0)
			return false;
	}

	if (suma != 0)
		return false;

	return true;
}
