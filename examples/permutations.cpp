#include "Permutations.hpp"
#include "../Benchmarks/external/rang.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using std::cout;
using std::stringstream;
using dscr::permutations;
using dscr::operator<<;

int n = 3;

void parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{	
	std::ios_base::sync_with_stdio(false);

	parse_command_line(argc,argv);
	
	for (auto& x : permutations(n))
		cout << x << '\n';
}

void parse_command_line(int argc, char* argv[])
{
	stringstream usage;
	usage	<< "Usage: permutations n\n"
			<< "Print to STDOUT the set of permutations of size n,\n\n"
			<< "Example:\n"
			<< "permutations " << n << "\n";
	if (argc == 2)
	{
		std::vector<std::string> arguments(argv + 1, argv + argc);
// 		cout << "arguments = " << arguments << endl;
		try
		{
			n = std::stoi(arguments[0]);
		}
		catch (...)
		{
			cout << "\nERROR: Argument must be a number\n\n";
			cout << usage.str();
			n = 3;
			return;
		}
		return;
	}

	cout << "ERROR: Wrong number of arguments\n\n";
	n = 3;
	cout << usage.str();
}
