#include "benchmark_all.hpp"
#include "TimeHelpers.hpp"

using namespace std;
using namespace dscr;

void testSpeed()
{
    binomial(33, 2);

    testCombinationsSpeed(32, 16);
    cout << flush;
    testLexCombinationsSpeed(32, 16);
    cout << flush;
    testPermutationsSpeed(11);
    cout << flush;
    testPartitionsSpeed(45);
    cout << flush;
    testMultisetSpeed();
    cout << flush;
    testDyckPathsSpeed(18);
    cout << flush;
    testMotzkinSpeed(20);
    cout << flush;
    testSetPartitionSpeed(13);
    cout << flush;
}

int main()
{
    Chronometer C;

    cout << "================ Starting Speed Tests ================" << endl;
    testSpeed();

    // 	produceAllCombinationBenchmarkData(25,34);

    cout << "Total Time taken = " << C.Reset() << "s" << endl;
    return 0;
}
