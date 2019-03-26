#include "nQueenSupport.h"

#include <iostream>
using std::cout;

std::atomic<int> solutionCount { 0 };

//==============================================================================
bool queensCollide(std::vector<unsigned> const &board)
{
    if(board.size() < 2)
        return false;
    unsigned newRow = board.size() - 1;
    for(unsigned row { 0 }; row < newRow; ++row)
    {
        // columns
        if(board[row] == board[newRow])
            return true;
        // diagonals
        unsigned diffX = newRow - row;

        unsigned v1 = board[row], v2 = board[newRow];
        unsigned diffY = v1 > v2 ? v1 - v2 : v2 - v1;

        if(diffX == diffY)
            return true;
    }
    return false;
}

//==============================================================================
void solveQueens(std::vector<unsigned> board, unsigned queenCount)
{
    for(unsigned newPos { 0 }; newPos < queenCount; ++newPos)
    {
        auto newBoard = board;
        newBoard.push_back(newPos);
        if(!queensCollide(newBoard))
        {
            if(newBoard.size() == queenCount)
                ++solutionCount;
            else
                solveQueens(newBoard, queenCount);
        }
    }
}
