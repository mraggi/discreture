#include "discreture.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;
using namespace dscr;

int main(int argc, char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	stringstream usage;
	usage	<< "Usage: dyck n [replacement-string]\n"
			<< "Print to STDOUT the set of dyck paths (catalan paths) of size 2n,\n"
			<< "where n is an integer and replacement-string is a set of two characters that play the role of 1 and -1.\n"
			<< "Example 1:\n"
			<< "dyck 3\n"
			<< "1 1 1 -1 -1 -1\n" 
			<< "1 1 -1 1 -1 -1\n" 
			<< "1 -1 1 1 -1 -1\n" 
			<< "1 1 -1 -1 1 -1\n" 
			<< "1 -1 1 -1 1 -1\n\n"
			<< "Example 2:\n"
			<< "dyck 3 \"()\"\n"
			<< "((()))\n"
			<< "(()())\n"
			<< "()(())\n"
			<< "(())()\n"
			<< "()()()\n";


	if (argc >= 2)
	{
		std::vector<std::string> arguments(argv + 1, argv + argc);
// 		cout << "arguments = " << arguments << endl;
		int n {0};

		try
		{
			n = std::stoi(arguments[0]);
		}
		catch (...)
		{
			cout << "\nERROR: First argument must be a number\n\n";
			cout << usage.str();
			return 0;
		}

		if (arguments.size() == 2)
		{
			if (arguments[1].size() != 2)
			{
				cout << "\nERROR: Second argument must be two characters long\n\n";
				cout << usage.str();
				return 0;
			}

			dyck_paths X(n);

			for (auto& x : X)
			{
				cout << dyck_paths::to_string(x, arguments[1]) << '\n';
			}

			return 0;
		} //then arguments.size() must be 2

		dyck_paths X(n);

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
