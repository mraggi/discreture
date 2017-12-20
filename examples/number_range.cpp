#include <cstdlib>
#include <string>
#include <sstream>
#include "discreture.hpp"

using namespace std;
using namespace dscr;

int main(int argc, char* argv[])
{
	std::ios_base::sync_with_stdio(false);
	stringstream usage;
	usage	<< "Usage: number_range a b step\n"
			<< "Print to STDOUT the set number_range from a to b with steps of size step\n"
			<< "where a,b and step integers.\n"
			<< "Example:\n"
			<< "./number_range 2 10 3\n"
			<< "2 5 8\n";

	if (argc == 4)
	{
		std::vector<std::string> arguments(argv + 1, argv + argc);

		int a, b, t;

		try
		{
			a = std::stoi(arguments[0]);
			b = std::stoi(arguments[1]);
			t = std::stoi(arguments[2]);
		}
		catch (...)
		{
			cout << "Arguments must be numbers\n";
			cout << usage.str();
			return 0;
		}

		number_range X(a,b,t);

		for (const auto& x : X)
		{
			cout << x << ' ';
		}

		return 0;
	}

	cout << "Wrong number of arguments\n";
	cout << usage.str();
	return 0;
}
