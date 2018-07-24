#include "Discreture/Motzkin.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

int n = 0; // Global variable for exposition purposes. Do not use global
           // variables in real code.

using std::cout;
using std::endl;
using discreture::motzkin_paths;
using discreture::operator<<;

// Just sets global variables n and k.
std::string parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false); // this makes terminal output a bit
                                           // faster.

    auto replacement_string = parse_command_line(argc, argv);

    if (replacement_string.size() == 3)
    {
        for (auto& x : motzkin_paths(n))
            cout << motzkin_paths::to_string(x, replacement_string) << endl;
    }
    else
    {
        for (auto& x : motzkin_paths(n))
            cout << x << endl;
    }
    return 0;
}

std::string parse_command_line(int argc, char* argv[])
{
    std::string replacement_string;
    std::stringstream usage;
    usage << "Usage: motzkin n [replacement-string]\n"
          << "Print to STDOUT the set of motzkin paths (catalan paths) of size "
             "2n,\n"
          << "where n is an integer and replacement-string is a set of three "
             "characters that play the role of 1, 0 and -1.\n\n"
          << "Example 1:\n"
          << "  ./motzkin 4\n"
          << "  0 0 0 0\n"
          << "  1 -1 0 0\n"
          << "  0 1 -1 0\n"
          << "  1 0 0 -1\n"
          << "  0 1 0 -1\n"
          << "  0 0 1 -1\n"
          << "  1 1 -1 -1\n"
          << "  1 -1 1 -1\n\n"
          << "Example 2:\n"
          << "  ./motzkin 3 \"(-)\"\n"
          << "  ---\n"
          << "  ()-\n"
          << "  (-)\n"
          << "  -()\n";

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
            cout << usage.str();
            return replacement_string;
        }

        if (arguments.size() == 2)
        {
            if (arguments[1].size() != 3)
            {
                cout << "\nERROR: Second argument must be three characters "
                        "long\n\n";
                cout << usage.str();
                n = 0;
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
