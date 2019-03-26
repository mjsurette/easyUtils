/*
    A board is represented by a vector of unsigned integers
    with each position in the vector represinting a row
    and the value representing a column.
            | | | | | |Q| | |
            | | | |Q| | | | |
            | | | | | | |Q| |
            |Q| | | | | | | |
            | | | | | | | |Q|
            | |Q| | | | | | |
            | | | | |Q| | | |
            | | |Q| | | | | |
    would be represented by the vector { 5,3,6,0,7,1,4,2 }
*/

#include "../test/nQueenSupport.h"
#include "threadPool.h"
// extern std::atomic<int> solutionCount; in nQueenSupport.h

#include <atomic>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr unsigned QUEENcount = 14; // default number of queens

//==============================================================================
int main(int argc, char **argv)
{
    unsigned noQueens = argc > 1 ? stoul(string(argv[1])) : 0;
    noQueens = noQueens == 0 ? QUEENcount : noQueens;

    cout << "nQueens " << noQueens << endl;
    easyUtils::ThreadPool tp;
    for(unsigned i { 0 }; i < noQueens; ++i)
    {
        std::vector<unsigned> board;
        board.reserve(noQueens);
        board.push_back(i);
        tp.addJob([=]() { solveQueens(std::move(board), noQueens); });
    }
    tp();
    tp.finish();

    cout << solutionCount << endl;
    return 0;
}
