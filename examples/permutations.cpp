#include "Permutations.hpp"
#include <cstdlib>
#include <sstream>
#include <string>


int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::stringstream;
	using dscr::permutations;
	using dscr::operator<<;
	std::ios_base::sync_with_stdio(false);

	stringstream usage;
	usage	<< "Usage: permutations n\n"
			<< "Print to STDOUT the set of permutations of size n,\n\n"
			<< "Example:\n"
			<< "permutations 3\n"
			<< "0 1 2\n"
			<< "0 2 1\n"
			<< "1 0 2\n"
			<< "1 2 0\n"
			<< "2 0 1\n" 
			<< "2 1 0\n";
	if (argc == 2)
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

		permutations X(n);

		for (auto& x : X)
		{
			cout << x << '\n';
		}
		return 0;
	}

	cout << "ERROR: Wrong number of arguments\n\n";
	cout << usage.str();
	return 0;
}
