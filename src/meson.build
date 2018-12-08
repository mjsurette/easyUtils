
easyUtilsSrc= ['readFileAsUTF8.cpp']
easyUtilsSrc+= ['threadPool.cpp']
easyUtilsSrc+= ['utfConvert.cpp']
easyUtilsSrc+= ['utfNess.cpp']

easyUtilsLib= library('easyUtils',easyUtilsSrc
    ,include_directories:easyUtilsInc)

easyUtilsDep= declare_dependency(
    link_with:easyUtilsLib,
    include_directories:easyUtilsInc
)
