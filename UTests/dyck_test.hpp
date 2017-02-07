#pragma once
#include "DyckPaths.hpp"
#include <vector>

bool testDyckPaths();
void testDyckPathsSpeed(int n);

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
