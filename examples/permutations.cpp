#include "Permutations.hpp"
#include <cstdlib>
#include <sstream>
#include <string>
#include "../Benchmarks/external/rang.hpp"

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
		
// 		permutations::permutation old(n,-1);
// 		int num = 0;
// 		std::vector<rang::fg> colors = {rang::fg::green, rang::fg::yellow, rang::fg::magenta, rang::fg::red, rang::fg::cyan};
		for (auto& x : X)
		{
// 			for (int i = 0; i < x.size(); ++i)
// 			{
// 				if (old[i] != x[i])
// 				{
// 					cout << colors[x[i]] << rang::style::bold;
// 				}
// 				cout << x[i] << ' ' << rang::style::reset;
// 				
// 			}
// 			cout << " --> " << num++ << '\n';
// 			old = x;
			cout << x << '\n';
		}
		return 0;
	}

	cout << "ERROR: Wrong number of arguments\n\n";
	cout << usage.str();
	return 0;
}
