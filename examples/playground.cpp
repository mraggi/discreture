// This file is my personal playground. I just use it to test stuff out.

#include "Discreture/Combinations.hpp"
#include <string_view>

using namespace std; // NOLINT
using namespace discreture; // NOLINT
using namespace discreture::detail; // NOLINT

int main()
{
    std::string X = "Hello world!";
	std::string_view A(X);
	std::cout << A << std::endl;
	
	for (auto&& a : discreture::combinations(A,3))
		cout << a << endl;

    return 0;
}
