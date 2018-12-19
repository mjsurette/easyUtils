
list(APPEND easyUtilsSOURCES readFileAsUTF8.cpp)
list(APPEND easyUtilsSOURCES threadPool.cpp)
list(APPEND easyUtilsSOURCES utfConvert.cpp)
list(APPEND easyUtilsSOURCES utfNess.cpp)
list(APPEND easyUtilsSOURCES uuencode.cpp)

add_library (easyUtils STATIC ${easyUtilsSOURCES})
