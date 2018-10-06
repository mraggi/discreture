// This file is my personal playground. I just use it to test stuff out.

#include "Discreture/detail/PartitionsDetail.hpp"
#include "discreture.hpp"

using namespace std; // NOLINT
using namespace discreture; // NOLINT
using namespace discreture::detail; // NOLINT

int main()
{
    int n = 8;

    auto P = partitions(n);
    auto part = P.begin();

    using partition = std::vector<int>;
    P.for_each([&part](const partition& p) {
        std::cout << p << " = " << *part << std::endl;
        ++part;
    });

    return 0;
}
