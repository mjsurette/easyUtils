
eightQueensFiles= ['test-main.cpp']
eightQueensFiles+= ['eightQueens.cpp']
executable('eightQueens',eightQueensFiles
    ,dependencies:[easyUtilsDep,threadDep]
    ,include_directories:Catch2Inc
)

textMapTestFiles= ['test-main.cpp']
textMapTestFiles+= ['textMapTest.cpp']
executable('textMapTest',textMapTestFiles
    ,dependencies:easyUtilsDep
    ,include_directories:Catch2Inc
)

uuencodeTestFiles= ['test-main.cpp']
uuencodeTestFiles+= ['uuencodeTest.cpp']
executable('uuencodeTest',uuencodeTestFiles
    ,dependencies:easyUtilsDep
    ,include_directories:Catch2Inc
)
