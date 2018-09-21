#include "Discreture/ArithmeticProgression.hpp"
#include "Discreture/VectorHelpers.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using discreture::arithmetic_progression;

int from = 2;
int to = 15;
int step = 3;

void parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    parse_command_line(argc, argv);

    for (auto x : arithmetic_progression{from, to, step})
        cout << x << ' ';
    cout << endl;

    return 0;
}

void parse_command_line(int argc, char* argv[])
{
    stringstream usage;
    usage << "Usage: arithmetic_progression a b step\n"
          << "Print to STDOUT the set arithmetic_progression from a to b with "
             "steps of "
             "size step\n"
          << "where a,b and step are integers. Step is 1 by default.\n"
          << "Example:\n"
          << "./arithmetic_progression " << from << ' ' << to << ' ' << step
          << '\n';

    if (argc > 4 || argc < 3)
    {
        cout << "\nERROR: Wrong number of arguments\n\n";
        cout << usage.str();
        return;
    }

    std::vector<std::string> arguments(argv + 1, argv + argc);

    try
    {
        int a, b;
        int t = 1;
        a = std::stoi(arguments[0]);
        b = std::stoi(arguments[1]);
        if (arguments.size() > 2)
            t = std::stoi(arguments[2]);

        if (t == 0)
            throw;

        from = a;
        to = b;
        step = t;
    }
    catch (...)
    {
        std::cerr << "\nERROR: Arguments must be numbers, with t != 0. "
                     "Additionally, a < b if t > 0, or a > b if t < 0. \n\n";
        std::cerr << usage.str();
        return;
    }
}
