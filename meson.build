project('discreture','cpp', 
        version : '1.9',
        default_options : ['warning_level=3', 'cpp_std=c++17', 'optimization=3', 'buildtype=release', 'b_ndebug=if-release'])

boost_dep = dependency('boost')

includes = include_directories('include')
discreture_dep = declare_dependency(include_directories: includes)

if get_option('BUILD_EXAMPLES')
    subdir('examples')
endif

if get_option('BUILD_TESTS')
    subdir('tests')
endif

if get_option('BUILD_BENCHMARKS')
    subdir('benchmarks')
endif
