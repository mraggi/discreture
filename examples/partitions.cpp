#include "Partitions.hpp"
#include <cstdlib>
#include <sstream>
#include <string>



int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::stringstream;
	using dscr::partitions;
	using dscr::operator<<;
	std::ios_base::sync_with_stdio(false);
	stringstream usage;
	usage	<< "Usage: setpartitions n [min_parts] [max_parts]\n"
			<< "Print to STDOUT the set of set partitions of size n, \n with an optional minimum number of parts and maximum number of parts\n"
			<< "Example 1:\n"
			<< "setpartitions 3\n"
			<< "[0][1][2]\n"
			<< "[0 1][2]\n"
			<< "[0 2][1]\n"
			<< "[1 2][0]\n"
			<< "[0 1 2]\n\n"
			<< "Example 2:\n"
			<< "setpartitions 4 2 3\n"
			<< "[0 1][2][3]\n"
			<< "[0 2][1][3]\n"
			<< "[0 3][1][2]\n"
			<< "[1 2][0][3]\n"
			<< "[1 3][0][2]\n"
			<< "[2 3][0][1]\n"
			<< "[0 1 2][3]\n"
			<< "[0 1 3][2]\n"
			<< "[0 2 3][1]\n"
			<< "[1 2 3][0]\n"
			<< "[0 1][2 3]\n"
			<< "[0 2][1 3]\n"
			<< "[0 3][1 2]\n";

	std::vector<std::string> arguments(argv + 1, argv + argc);
	
	if (arguments.empty() || arguments.size() > 3)
	{

		cout << "ERROR: Wrong number of arguments\n\n";
		cout << usage.str();
		return 0;
	}
	
	int n;
	try
	{
		n = std::stoi(arguments[0]);
	}
	catch (...)
	{
		cout << "ERROR: Arguments must be numbers\n\n";
		cout << usage.str();
		return 0;
	}
	int min_parts {1};
	int max_parts {n};

	if (arguments.size() == 2)
	{
		try
		{
			min_parts = std::stoi(arguments[1]);
			max_parts = min_parts;
		}
		catch (...)
		{
			cout << "ERROR: Arguments must be numbers\n\n";
			cout << usage.str();
			return 0;
		}
	}
	
	if (arguments.size() == 3)
	{
		try
		{
			min_parts = std::stoi(arguments[1]);
			max_parts = std::stoi(arguments[2]);
		}
		catch (...)
		{
			cout << "ERROR: Arguments must be numbers\n\n";
			cout << usage.str();
			return 0;
		}
	}
	if (min_parts > max_parts)
	{
		cout << "ERROR: minimum number of parts must be greater or equal to maximum number of parts\n\n";
		cout << usage.str();
		return 0;
	}
	if (min_parts <= 0)
	{
		cout << "ERROR: cannot have 0 or less parts!\n\n";
		cout << usage.str();
		return 0;
	}
	
	if (max_parts > n)
	{
		cout << "ERROR: cannot have more than n parts!\n\n";
		cout << usage.str();
		return 0;
	}
		
	
	partitions X(n,min_parts,max_parts);

	for (auto& x : X)
	{
		cout << x << endl;
	}
	
	return 0;
}
