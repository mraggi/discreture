#include "misc_test.hpp"
#include "TimeHelpers.hpp"

using namespace dscr;
using namespace std;

void testVectorHelpers()
{
	vector<float> A = {0.2, 0.3, 0.8};
	auto B = A / 8.0;
	std::cout << B << '\n';
}
