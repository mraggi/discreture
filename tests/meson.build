
gtest_dep = dependency('gtest', main : false, required : false)

if gtest_dep.found()
    test_exe = executable('unittests.x', 
                          'arithmetic_progression_tests.cpp', 
                          'combination_tests.cpp', 
                          'dyck_tests.cpp', 
                          'idxview_container_tests.cpp', 
                          'integer_interval_tests.cpp', 
                          'lex_combinations_tests.cpp', 
                          'main.cpp', 
                          'motzkin_tests.cpp', 
                          'multiset_tests.cpp', 
                          'partition_tests.cpp', 
                          'permutation_tests.cpp', 
                          'reversed_tests.cpp', 
                          'sequence_tests.cpp', 
                          'set_partition_tests.cpp', 
                          dependencies : [boost_dep,gtest_dep,discreture_dep])
    test('gtest test', test_exe)
endif
