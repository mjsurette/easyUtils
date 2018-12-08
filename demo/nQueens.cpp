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

#include "threadPool.h"

#include <atomic>
#include <iostream>
#include <vector>
using namespace std;

constexpr unsigned QUEENcount = 14;

atomic<int> solutionCount = 0;

//==============================================================================
bool queensCollide(std::vector<unsigned> const &board)
{
    if (board.size() < 2)
        return false;
    unsigned newRow = board.size() - 1;
    for (unsigned row = 0; row < newRow; ++row)
    {
        // columns
        if (board[row] == board[newRow])
            return true;
        // diagonals
        unsigned diffX = newRow - row;

        unsigned v1 = board[row], v2 = board[newRow];
        unsigned diffY = v1 > v2 ? v1 - v2 : v2 - v1;

        if (diffX == diffY)
            return true;
    }
    return false;
}

//==============================================================================
void solveQueens(std::vector<unsigned> board)
{
    for (unsigned newPos = 0; newPos < QUEENcount; ++newPos)
    {
        auto newBoard = board;
        newBoard.push_back(newPos);
        if (!queensCollide(newBoard))
        {
            if (newBoard.size() == QUEENcount)
                ++solutionCount;
            else
                solveQueens(newBoard);
        }
    }
}

//==============================================================================
int main()
{
    cout << "nQueens" << endl;
    easyUtils::ThreadPool tp;
    for (unsigned i = 0; i < QUEENcount; ++i)
    {
        std::vector<unsigned> board;
        board.reserve(QUEENcount);
        board.push_back(i);
        tp.addJob([=]() { solveQueens(std::move(board)); });
    }
    tp();
    tp.finish();

    cout << solutionCount << endl;
    return 0;
}
