#include "Discreture/Multisets.hpp"
#include <cstdlib>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using discreture::multisets;
using discreture::operator<<;

std::vector<int> total;

void parse_command_line(int argc, char* argv[]);

int main(int argc, char* argv[])
{

    std::ios_base::sync_with_stdio(false);

    parse_command_line(argc, argv);

    multisets X(total);
    for (auto&& x : X)
        cout << x << endl;

    return 0;
}

void parse_command_line(int argc, char* argv[])
{
    std::stringstream usage;
    usage << "Usage: multisets [integer params]\n"
          << "Print to STDOUT all submultisets of the given multiset.\n\n"
          << "Example:\n\n"
          << "./multisets 1 2 0 1\n";

    std::vector<std::string> arguments(argv + 1, argv + argc);
    try
    {
        for (auto&& arg : arguments)
        {
            total.emplace_back(std::stoi(arg));
        }
    }
    catch (...)
    {
        cout << "\nERROR: All arguments must be numbers\n\n";
        total = {1, 2, 0, 1};
        cout << usage.str();
        return;
    }

    if (total.empty())
    {
        total = {1, 2, 0, 1};
        cout << usage.str();
    }
}
