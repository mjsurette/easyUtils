
#include "catch.hpp"

#include "nQueenSupport.h"
#include "threadPool.h"
// extern std::atomic<int> solutionCount; in nQueenSupport.h

#include <atomic>
#include <vector>
using namespace std;

constexpr unsigned QUEENcount = 8;

//==============================================================================
TEST_CASE("eight queens test")
{
    easyUtils::ThreadPool tp;
    for(unsigned i { 0 }; i < QUEENcount; ++i)
    {
        std::vector<unsigned> board;
        board.reserve(QUEENcount);
        board.push_back(i);
        tp.addJob([=]() { solveQueens(std::move(board), QUEENcount); });
    }
    tp();
    tp.finish();

    REQUIRE(solutionCount == 92);
}
