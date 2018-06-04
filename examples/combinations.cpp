#include "Discreture/Combinations.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using dscr::combinations;
using dscr::operator<<;

int n = 5; // Global variable for exposition purposes. Do not use global
           // variables in real code.
string N;
int k = 3;

// Just sets global variables n and k.
void parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(
      false); // this makes terminal output a bit faster.

    parse_command_line(argc, argv);

    if (N.empty())
    {
        for (auto& x : combinations(n, k))
            cout << x << endl;
    }
    else
    {
        for (auto x : combinations(N, k))
            cout << x << endl;
    }
    return 0;
}

void parse_command_line(int argc, char* argv[])
{
    std::stringstream usage;
    usage << "Usage: combinations n k\n"
          << "Print to STDOUT the set of combinations of size k of a subset of "
             "size n,\n"
          << "where k is an integer and n is either a string or an integer.\n"
          << "Example:\n"
          << "./combinations " << n << " " << k << "\n";

    if (argc != 3)
    {
        cout << "\nERROR: Wrong number of arguments!\n\n";
        cout << usage.str();
        return;
    }

    std::vector<std::string> arguments(argv + 1, argv + argc);

    try
    {
        int ntemp = std::stoi(arguments[0]);
        n = ntemp;
    }
    catch (...)
    {
        N = arguments[0];
    }

    try
    {
        int ktemp = std::stoi(arguments[1]);

        if (ktemp < 0)
            throw;
        // only set if there were no errors
        k = ktemp;
    }
    catch (...)
    {
        cout << "\nERROR: Second argument must be a non-negative integer!\n\n";
        cout << usage.str();
        return;
    }
}
