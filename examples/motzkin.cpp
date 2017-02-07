#include <cstdlib>
#include <sstream>
#include "Motzkin.hpp"
#include <string>

using namespace std;
using namespace dscr;

int main(int argc, char* argv[])
{
	std::ios_base::sync_with_stdio(false);
	stringstream usage;
	usage	<< "Usage: motzkin n [replacement-string]\n"
			<< "Print to STDOUT the set of motzkin paths of size n,\n"
			<< "where n is an integer and replacement-string is a set of three characters that play the role of 1, 0 and -1.\n\n"
			<< "Example 1:\n"
			<< "motzkin 4\n"
			<< "0 0 0 0\n"
			<< "1 -1 0 0\n" 
			<< "1 0 -1 0 \n"
			<< "0 1 -1 0 \n"
			<< "1 0 0 -1 \n"
			<< "0 1 0 -1 \n"
			<< "0 0 1 -1 \n"
			<< "1 1 -1 -1 \n"
			<< "1 -1 1 -1\n\n"
			<< "Example 2:\n"
			<< "motzkin 4 \"(-)\"\n"
			<< "----\n"
			<< "()--\n"
			<< "(-)-\n"
			<< "-()-\n"
			<< "(--)\n"
			<< "-(-)\n"
			<< "--()\n"
			<< "(())\n"
			<< "()()\n";

	if (argc >= 2)
	{
		std::vector<std::string> arguments(argv + 1, argv + argc);

		int n {0};

		try
		{
			n = std::stoi(arguments[0]);
		}
		catch (...)
		{
			cout << "First argument must be a number\n";
			cout << usage.str();
			return 0;
		}

		if (arguments.size() == 2)
		{
			if (arguments[1].size() != 3)
			{
				cout << "Second argument must be two characters long\n";
				cout << usage.str();
				return 0;
			}

			motzkin_paths X(n);

			for (auto& x : X)
			{
				cout << motzkin_paths::to_string(x, arguments[1]) << '\n';
			}

			return 0;
		} //then arguments.size() must be 2

		motzkin_paths X(n);

		for (auto& x : X)
		{
			cout << x << '\n';
		}

		return 0;

	}

	cout << "Wrong number of arguments\n";
	cout << usage.str();
	return 0;
}
