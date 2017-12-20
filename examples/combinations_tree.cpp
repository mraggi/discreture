#include "discreture.hpp"
#include <cstdlib>
#include <sstream>
#include <string>


int main(int argc, char* argv[])
{
	
	using std::cout;
	using std::endl;
	using std::stringstream;
	using dscr::combinations_tree;
	using dscr::operator<<;
	std::ios_base::sync_with_stdio(false);
	stringstream usage;
	usage	<< "Usage: combinations_tree n k\n"
			<< "Print to STDOUT the set of combinations of size k of a subset of size n in tree order (lexicographic),\n"
			<< "where n and k are integers.\n"
			<< "Example:\n"
			<< "./combinations_tree 5 3\n"
			<< "0 1 2\n"
			<< "0 1 3\n"
			<< "0 1 4\n"
			<< "0 2 3\n"
			<< "0 2 4\n"
			<< "0 3 4\n"
			<< "1 2 3\n"
			<< "1 2 4\n"
			<< "1 3 4\n"
			<< "2 3 4\n";

	if (argc == 3)
	{
		std::vector<std::string> arguments(argv + 1, argv + argc);

		int n, k;

		try
		{
			n = std::stoi(arguments[0]);
			k = std::stoi(arguments[1]);
		}
		catch (...)
		{
			cout << "Arguments must be numbers\n";
			cout << usage.str();
			return 0;
		}

		combinations_tree X(n, k);
		cout << "Size = " << X.size() << endl;
		for (const auto& x : X)
		{
			cout << x << '\n';
		}

		return 0;
	}

	cout << "Wrong number of arguments\n";
	cout << usage.str();
	return 0;
}
