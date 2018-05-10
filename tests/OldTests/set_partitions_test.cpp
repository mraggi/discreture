#include "set_partitions_test.hpp"
#include "TimeHelpers.hpp"
using namespace dscr;

bool testSetPartitions()
{
    std::cout << "============= Testing Set Partitions ============"
              << std::endl;

    set_partitions X(4);
    int i = 0;
    std::cout << "\nHere are all sets partitions with 4 elements" << std::endl;

    for (auto& x : X)
    {
        for (auto& t : x)
            std::cout << '|' << t;
        std::cout << '|' << std::endl;
        ++i;
    }
    std::cout << "\nHere are all set partitions of 6 with either 3 or 4 parts"
              << std::endl;

    set_partitions Y(6, 3, 4);

    for (auto& y : Y)
    {
        for (auto& t : y)
            std::cout << '|' << t;
        std::cout << '|' << std::endl;
    }

    return true;
}
