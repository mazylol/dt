project('dt', 'cpp', default_options : ['cpp_std=c++23'])

dependency_json = dependency('nlohmann_json', required : true)

cmake = import('cmake')
argparse_subproj = cmake.subproject('argparse')
argparse_lib = argparse_subproj.dependency('argparse')

src = [
    'src/main.cpp',
    'src/lockfile.cpp',
    'src/lockfile.hpp',
    'src/commands/commands.hpp',
    'src/commands/init.cpp'
]

executable('dt', sources : src, dependencies : [dependency_json, argparse_lib], install : true)
