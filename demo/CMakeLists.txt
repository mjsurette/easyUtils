
list(APPEND nQueensFiles ../test/nQueenSupport.cpp)
list(APPEND nQueensFiles nQueens.cpp)
add_executable(nQueens ${nQueensFiles})
target_link_libraries(nQueens easyUtils)
target_link_libraries(nQueens Threads::Threads)

list(APPEND readFileFiles readFile.cpp)
add_executable(readFile ${readFileFiles})
target_link_libraries(readFile easyUtils)

list(APPEND standardPathsFiles standardPaths.cpp)
add_executable(standardPaths ${standardPathsFiles})
target_link_libraries(standardPaths easyUtils)

list(APPEND readFileByLineFiles readFileByLine.cpp)
add_executable(readFileByLine ${readFileByLineFiles})
target_link_libraries(readFileByLine easyUtils)

list(APPEND utfNessFiles utfNess.cpp)
add_executable(utfNess ${utfNessFiles})
target_link_libraries(utfNess easyUtils)

list(APPEND uuidFiles uuid.cpp)
add_executable(uuid ${uuidFiles})
target_link_libraries(uuid easyUtils)
