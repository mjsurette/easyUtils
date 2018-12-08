
project('easyUtils','cpp'
    ,default_options:
    [   'cpp_std=c++17'
        ,'default_library=static'
    ]
)

easyUtilsInc= include_directories('include')

threadDep = dependency('threads')

subdir('src')

if get_option('build_tests')
    Catch2Inc = include_directories('subprojects/Catch2/single_include/catch2')
    subdir('test')
    subdir('demo')
endif
