
#include "catch.hpp"

#include "threadPool.h"

#include <atomic>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

constexpr unsigned QUEENScount = 8;

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
    for (unsigned newPos = 0; newPos < QUEENScount; ++newPos)
    {
        auto newBoard = board;
        newBoard.push_back(newPos);
        if (!queensCollide(newBoard))
        {
            if (newBoard.size() == QUEENScount)
                ++solutionCount;
            else
                solveQueens(newBoard);
        }
    }
}

//==============================================================================
TEST_CASE("eight queens test")
{
    easyUtils::ThreadPool tp;
    for (unsigned i = 0; i < QUEENScount; ++i)
    {
        std::vector<unsigned> board;
        board.reserve(QUEENScount);
        board.push_back(i);
        tp.addJob([=]() { solveQueens(std::move(board)); });
    }
    tp();
    tp.finish();

    REQUIRE(solutionCount == 92);
}
