#pragma once

#include <chrono>
#include <string>
#include <string_view>

namespace easyUtils
{
//==============================================================================
class UUID
{
    uint64_t _ab;
    uint64_t _cd;

public:
    UUID();
    UUID(std::string_view sv);

    std::string tostring();
    std::chrono::system_clock::time_point timestamp();
};
} // end namespace easyUtils
