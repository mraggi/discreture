#include "discreture.hpp"
#include <cstdlib>
#include <string>

using namespace std;
using namespace dscr;

int main(int argc, char* argv[])
{
	if (argc >= 3)
	{
		bool lexicographic = false;
		bool reverse = false;
		std::vector<std::string> arguments(argv + 1, argv + argc);

		if (arguments.size() > 2)
		{
			std::sort(arguments.begin() + 2, arguments.end());

			if (arguments[2] == "-l" ||
					arguments[2] == "--lexicographic" ||
					arguments[2] == "-rl" ||
					arguments[2] == "-lr")
				lexicographic = true;

			if (arguments[2] == "-r" ||
					arguments[2] == "--reverse" ||
					arguments[2] == "-rl" ||
					arguments[2] == "-lr")
				reverse = true;

			if (arguments.size() > 3)
			{
				if (arguments[3] == "-r" ||
						arguments[3] == "--reverse")
					reverse = true;
			}
		}

		int n, k;

		try
		{
			n = std::stoi(arguments[0]);
			k = std::stoi(arguments[1]);
		}
		catch (...)
		{
			cout << "Both arguments should be numbers!\n";
			cout << "Usage: combinations n k\n";
			return 0;
		}

		if (!lexicographic && !reverse)
		{
			combinations X(n, k);

			for (auto& x : X)
			{
				for (auto t : x) cout << t << " ";

				cout << endl;
			}
		}

		if (lexicographic && !reverse)
		{
			combinations_tree X(n, k);

			for (auto& x : X)
			{
				for (auto t : x) cout << t << " ";

				cout << endl;
			}
		}

		if (!lexicographic && reverse)
		{
			combinations X(n, k);

			for (auto i = X.rbegin(); i != X.rend(); ++i)
			{
				for (auto t : *i) cout << t << " ";

				cout << endl;
			}
		}

		if (lexicographic && reverse)
		{
			combinations_tree X(n, k);

			for (auto i = X.rbegin(); i != X.rend(); ++i)
			{
				for (auto t : *i) cout << t << " ";

				cout << endl;
			}
		}

		return 0;
	}

	cout << "Usage: combinations [n] [k] [OPTIONAL ORDER]\n"
		 << "Print to STDOUT the set of combinations of size k of a subset of size n\n"
		 << "Where n and k are integers.\n"
		 << "Order can be one of the following: \n"
		 << "  -l,--lexicographic\tSet order to lexicographic\n"
		 << "  -r,--reverse\t Start from end\n"
		 << "Example:\n"
		 << "./combinations 5 3\n"
		 << "0 1 2\n"
		 << "0 1 3\n"
		 << "0 2 3\n"
		 << "1 2 3\n"
		 << "0 1 4\n"
		 << "0 2 4\n"
		 << "1 2 4\n"
		 << "0 3 4\n"
		 << "1 3 4\n"
		 << "2 3 4\n";


}
