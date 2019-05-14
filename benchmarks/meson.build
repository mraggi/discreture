# BENCHMARKS

#inc = include_directories('.')

gsl_dep = dependency('gsl', required: false)

if gsl_dep.found()
    cpp_add_gsl_if_found = ['-DTEST_GSL_COMBINATIONS']
else
    cpp_add_gsl_if_found = []
endif

compiler = meson.get_compiler('cpp')
cpp_optimization_args = ['-Ofast','-mtune=native']

if compiler.get_id() == 'msvc'
    cpp_optimization_args = []
endif

bench = executable('discreture_benchmark',
           'combs.cpp',
           'dyckmotzkin.cpp',
           'main.cpp',
           'multisets.cpp',
           'partitions.cpp',
           'perms.cpp', dependencies : [gsl_dep,boost_dep,discreture_dep], cpp_args: cpp_add_gsl_if_found + cpp_optimization_args)
benchmark('bench', bench)

threads_dep = dependency('threads', required : false)
if threads_dep.found()
    bench_par = executable('parallel_benchmark', 'parallel/parallel_benchmarks.cpp', dependencies : [boost_dep,threads_dep,discreture_dep])
    benchmark('bench_par', bench_par)
endif
