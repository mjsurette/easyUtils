
list(APPEND eightQueensFiles test-main.cpp)
list(APPEND eightQueensFiles eightQueens.cpp)
add_executable(eightQueens ${eightQueensFiles})
target_link_libraries(eightQueens easyUtils)
target_link_libraries(eightQueens Threads::Threads)

list(APPEND textMapTestFiles test-main.cpp)
list(APPEND textMapTestFiles textMapTest.cpp)
add_executable(textMapTest ${textMapTestFiles})

list(APPEND uuencodeTestFiles test-main.cpp)
list(APPEND uuencodeTestFiles uuencodeTest.cpp)
add_executable(uuencodeTest ${uuencodeTestFiles})
target_link_libraries(uuencodeTest easyUtils)
