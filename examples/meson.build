executable('arithmetic_progression', 'arithmetic_progression.cpp', dependencies: [discreture_dep, boost_dep])
executable('combinations_reverse', 'combinations_reverse.cpp',dependencies: [discreture_dep, boost_dep])
executable('combinations', 'combinations.cpp',dependencies: [discreture_dep, boost_dep])
executable('dyck', 'dyck.cpp',dependencies: [discreture_dep, boost_dep])
executable('lex_combinations_reverse', 'lex_combinations_reverse.cpp',dependencies: [discreture_dep, boost_dep])
executable('lex_combinations', 'lex_combinations.cpp',dependencies: [discreture_dep, boost_dep])
executable('motzkin', 'motzkin.cpp',dependencies: [discreture_dep, boost_dep])
executable('multisets', 'multisets.cpp',dependencies: [discreture_dep, boost_dep])
executable('partitions_reverse', 'partitions_reverse.cpp',dependencies: [discreture_dep, boost_dep])
executable('partitions', 'partitions.cpp',dependencies: [discreture_dep, boost_dep])
executable('permutations', 'permutations.cpp',dependencies: [discreture_dep, boost_dep])

compiler = meson.get_compiler('cpp')
message('COMPILER: ', compiler.get_id())

tbb_dep = meson.get_compiler('cpp').find_library('tbb',required:true)
executable('playground', 'playground.cpp',dependencies: [discreture_dep, boost_dep,tbb_dep])
executable('set_partitions', 'set_partitions.cpp',dependencies: [discreture_dep, boost_dep])
executable('tutorial', 'tutorial.cpp',dependencies: [discreture_dep, boost_dep])

threads_dep = dependency('threads', required : false)
if threads_dep.found()
    executable('tutorial_parallel', 'tutorial_parallel.cpp',dependencies: [discreture_dep,threads_dep,boost_dep])
endif
