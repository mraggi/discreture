#include "Discreture/Partitions.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using discreture::partitions;
using discreture::operator<<;

int n = 6;
int min_parts = 1;
int max_parts = n;

void parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    parse_command_line(argc, argv);

    partitions X(n, min_parts, max_parts);

    for (auto it = X.rbegin(); it != X.rend(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}

void reset()
{
    n = 6;
    min_parts = 1;
    max_parts = n;
}

void parse_command_line(int argc, char* argv[])
{
    stringstream usage;
    usage << "Usage: partitions_reverse n [min_parts] [max_parts]\n"
          << "Print to STDOUT all partitions_reverse of n, \n with an optional "
             "minimum number of parts and maximum number of parts\n\n"
          << "Example: "
          << "./partitions_reverse 6\n";

    std::vector<std::string> arguments(argv + 1, argv + argc);

    if (arguments.empty() || arguments.size() > 3)
    {

        cout << "\nERROR: Wrong number of arguments. Give between 1 and 3 "
                "arguments.\n\n";
        cout << usage.str();
        reset();
        return;
    }

    try
    {
        n = std::stoi(arguments[0]);
        max_parts = n;
    }
    catch (...)
    {
        cout << "\nERROR: Arguments must be numbers\n\n";
        reset();
        cout << usage.str();
        return;
    }

    if (arguments.size() == 2)
    {
        try
        {
            min_parts = std::stoi(arguments[1]);
            max_parts = min_parts;
        }
        catch (...)
        {
            reset();
            cout << "\nERROR: Arguments must be numbers\n\n";
            cout << usage.str();
            return;
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
            reset();
            cout << "\nERROR: Arguments must be numbers\n\n";
            cout << usage.str();
            return;
        }
    }
    if (min_parts > max_parts)
    {
        cout << "\nERROR: minimum number of parts must be greater or equal to "
                "maximum number of parts\n\n";
        reset();
        cout << usage.str();
        return;
    }
    if (min_parts <= 0)
    {
        cout << "\nERROR: cannot have 0 or less parts!\n\n";
        reset();
        cout << usage.str();
        return;
    }

    if (max_parts > n)
    {
        cout << "\nERROR: cannot have more than n parts!\n\n";
        reset();
        cout << usage.str();
        return;
    }
}
