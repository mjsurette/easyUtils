
cppCompiler = meson.get_compiler('cpp')
filesystemLib = cppCompiler.find_library('stdc++fs', required : false)

easyUtilsSrc= ['readFileAsUTF8.cpp']
easyUtilsSrc+= ['standardPaths.cpp']
easyUtilsSrc+= ['threadPool.cpp']
easyUtilsSrc+= ['utfConvert.cpp']
easyUtilsSrc+= ['utfNess.cpp']
easyUtilsSrc+= ['uuencode.cpp']
easyUtilsSrc+= ['uuid.cpp']

easyUtilsLib= library('easyUtils',easyUtilsSrc
    ,dependencies:filesystemLib
    ,include_directories:[easyUtilsInc,dateInc])

easyUtilsDep= declare_dependency(
    link_with:easyUtilsLib,
    include_directories:easyUtilsInc
)
