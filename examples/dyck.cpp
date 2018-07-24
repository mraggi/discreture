#include "Discreture/DyckPaths.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

int n = 0; // Global variable for exposition purposes. Do not use global
           // variables in real code.

using std::cout;
using std::endl;
using discreture::dyck_paths;
using discreture::operator<<;

// Just sets global variables n and k.
std::string parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false); // this makes terminal output a bit
                                           // faster.

    auto replacement_string = parse_command_line(argc, argv);

    if (replacement_string.size() == 2)
    {
        for (auto& x : dyck_paths(n))
            cout << dyck_paths::to_string(x, replacement_string) << endl;
    }
    else
    {
        for (auto& x : dyck_paths(n))
            cout << x << endl;
    }
    return 0;
}

std::string parse_command_line(int argc, char* argv[])
{
    std::string replacement_string;

    std::stringstream usage;
    usage
      << "Usage: dyck n [replacement-string]\n"
      << "Print to STDOUT the set of dyck paths (catalan paths) of size 2n,\n"
      << "where n is an integer and replacement-string is a set of two "
         "characters that play the role of 1 and -1.\n\n"
      << "Example 1:\n"
      << "  ./dyck 3\n"
      << "  1 1 1 -1 -1 -1\n"
      << "  1 1 -1 1 -1 -1\n"
      << "  1 -1 1 1 -1 -1\n"
      << "  1 1 -1 -1 1 -1\n"
      << "  1 -1 1 -1 1 -1\n\n"
      << "Example 2:\n"
      << "  ./dyck 3 \"()\"\n"
      << "  ((()))\n"
      << "  (()())\n"
      << "  ()(())\n"
      << "  (())()\n"
      << "  ()()()\n";

    if (argc >= 2)
    {
        std::vector<std::string> arguments(argv + 1, argv + argc);
        // 		cout << "arguments = " << arguments << endl;
        try
        {
            n = std::stoi(arguments[0]);
        }
        catch (...)
        {
            cout << "\nERROR: First argument must be a number\n\n";
            n = 0;
            cout << usage.str();
            return replacement_string;
        }

        if (arguments.size() == 2)
        {
            if (arguments[1].size() != 2)
            {
                cout
                  << "\nERROR: Second argument must be two characters long\n\n";
                n = 0;
                cout << usage.str();
                return replacement_string;
            }
            replacement_string = arguments[1];

            return replacement_string;
        } // then arguments.size() must be 2
        return replacement_string;
    }

    cout << "Wrong number of arguments\n";
    cout << usage.str();
    return replacement_string;
}
