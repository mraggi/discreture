#include "Discreture/SetPartitions.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using discreture::set_partitions;
using discreture::operator<<;

const int default_num = 4;
int n = default_num;
int min_parts = 1;
int max_parts = n;

void parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    parse_command_line(argc, argv);

    set_partitions X(n, min_parts, max_parts);

    for (auto&& x : X)
    {
        for (auto&& part : x)
        {
            cout << "[" << part << "]";
        }
        cout << endl;
    }

    return 0;
}

void reset()
{
    n = default_num;
    min_parts = 1;
    max_parts = n;
}

void parse_command_line(int argc, char* argv[])
{
    stringstream usage;
    usage << "Usage: set_partitions n [min_parts] [max_parts]\n"
          << "Print to STDOUT all partitions of {0,1,...,n-1} into distinct "
             "sets, \n"
          << "with an optional minimum number of parts and maximum number of "
             "parts\n\n"
          << "Example:\n"
          << "./set_partitions " << n << '\n';

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
