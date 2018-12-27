#include "uuid.h"

#include "date.h"
using namespace date;

#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>
#include <string_view>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::time_point_cast;
using TICKS = std::chrono::duration<int64_t, ratio<100, 1'000'000'000>>;

namespace easyUtils
{
// The UUID spec wants the number of 100 nanosecond intervals since Jan 1, 1601
// This implementation fills the remaining bits with a random number
//==============================================================================
UUID::UUID()
{
    date::sys_days refDate(1601_y / jan / 1);
    auto now = std::chrono::system_clock::now();

    auto ref = duration_cast<TICKS>(now - refDate);
    _ab = ref.count();

    std::random_device rd;
    std::mt19937_64 generator;
    generator.seed(rd());
    std::uniform_int_distribution<int64_t> distribution;
    _cd = distribution(generator);
}

//==============================================================================
UUID::UUID(std::string_view o)
{
    auto a = std::string(o.substr(0, 8));
    _ab = static_cast<uint64_t>(stol(a, nullptr, 16)) << 32;

    auto b = std::string(o.substr(9, 4));
    b += std::string(o.substr(14, 4));
    _ab |= static_cast<uint64_t>(stol(b, nullptr, 16));

    auto c = std::string(o.substr(19, 4));
    c += std::string(o.substr(24, 4));
    _cd = static_cast<uint64_t>(stol(c, nullptr, 16)) << 32;

    auto d = std::string(o.substr(28, 8));
    _cd |= static_cast<uint64_t>(stol(d, nullptr, 16));
}

//==============================================================================
std::string UUID::tostring()
{
    std::stringstream ss;
    ss << std::hex << std::nouppercase << std::setfill('0');

    uint32_t a = (_ab >> 32);
    uint32_t b = (_ab & 0xFFFFFFFF);
    uint32_t c = (_cd >> 32);
    uint32_t d = (_cd & 0xFFFFFFFF);

    ss << std::setw(8) << (a) << '-';
    ss << std::setw(4) << (b >> 16) << '-';
    ss << std::setw(4) << (b & 0xFFFF) << '-';
    ss << std::setw(4) << (c >> 16) << '-';
    ss << std::setw(4) << (c & 0xFFFF);
    ss << std::setw(8) << d;

    return ss.str();
}

//==============================================================================
std::chrono::system_clock::time_point UUID::timestamp()
{
    date::sys_days refDate(1601_y / jan / 1);
    TICKS ts { _ab };
    return ts + refDate;
}

} // end namespace easyUtils
