#pragma once

#include <atomic>
#include <vector>

extern std::atomic<int> solutionCount;

bool queensCollide(std::vector<unsigned> const &board);
void solveQueens(std::vector<unsigned> board, unsigned queenCount);
