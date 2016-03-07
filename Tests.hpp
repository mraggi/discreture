#pragma once

#include "discreture.hpp"

// using namespace dscr;

void testVectorHelpers();
void testMisc();
bool testCombinations();
bool testPermutations();
bool testSubsets();
bool testMultiset();
bool testPartitions();
bool testDyckPaths();
bool testMotzkin();
bool testProbability();

void testCombinationsSpeed(int n = 32, int k = 16);
void testPermutationsSpeed(int n = 12);
void testSubsetsSpeed(int n = 29);
void testPartitionsSpeed(int n = 90);
void testMultisetSpeed();
void testDyckPathsSpeed(int n = 18);
void testMotzkinSpeed(int n = 20);

// void testGSLCombinations(); // uncomment to test GSL combinations
void testManualCombinations();

void testCorrectness();
void testSpeed();