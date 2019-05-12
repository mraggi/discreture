project('discreture','cpp', 
        version : '1.9',
        default_options : ['warning_level=3', 'cpp_std=c++14', 'optimization=3','buildtype=release'])

boost_dep = dependency('boost')

includes = include_directories('include')

if get_option('BUILD_EXAMPLES')
    subdir('examples')
endif

if get_option('BUILD_TESTS')
    subdir('tests')
endif

if get_option('BUILD_BENCHMARKS')
    subdir('benchmarks')
endif
