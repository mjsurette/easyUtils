
list(APPEND easyUtilsSOURCES readFileAsUTF8.cpp)
list(APPEND easyUtilsSOURCES standardPaths.cpp)
list(APPEND easyUtilsSOURCES threadPool.cpp)
list(APPEND easyUtilsSOURCES utfConvert.cpp)
list(APPEND easyUtilsSOURCES utfNess.cpp)
list(APPEND easyUtilsSOURCES uuencode.cpp)
list(APPEND easyUtilsSOURCES uuid.cpp)

add_library (easyUtils STATIC ${easyUtilsSOURCES})
target_link_libraries(easyUtils stdc++fs)
