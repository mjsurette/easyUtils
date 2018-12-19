
#include "uuencode.h"

#include <array>
#include <stdexcept>
#include <string>
#include <string_view>
using namespace std;

namespace easyUtils
{
//==============================================================================
string uuencode(string_view sv)
{
    string rv;
    rv.reserve(60);
    if (sv.size() > 45)
        sv = sv.substr(0, 45);

    uint16_t t1, t2;
    string ts;
    while (sv.size() > 0)
    {
        if (sv.size() < 3)
        {
            ts = string(sv) + "  "s;
            sv = string_view(ts).substr(0, 3);
        }
        t1 = static_cast<uint16_t>(sv[0]) >> 2;
        rv += static_cast<char>(t1 + 32);

        t1 = static_cast<uint16_t>(sv[0]) << 4;
        t2 = static_cast<uint16_t>(sv[1]) >> 4;
        rv += static_cast<char>(((t1 | t2) & 0x3F) + 32);

        t1 = static_cast<uint16_t>(sv[1]) << 2;
        t2 = static_cast<uint16_t>(sv[2]) >> 6;
        rv += static_cast<char>(((t1 | t2) & 0x3F) + 32);

        rv += static_cast<char>((sv[2] & 0x3F) + 32);

        sv = sv.substr(3);
    }
    rv.shrink_to_fit();
    return rv;
}

//==============================================================================
vector<uint8_t> uudecode(string_view sv)
{
    vector<uint8_t> rv;
    if (sv.size() > 60)
        sv = sv.substr(0, 60);
    while (sv.size() > 0)
    {
        if (sv.size() < 4)
            throw length_error("length error in uudecode");

        uint16_t t1, t2;
        t1 = (static_cast<uint16_t>(sv[0]) - 32) << 2;
        t2 = (static_cast<uint16_t>(sv[1]) - 32) >> 4;
        rv.push_back(static_cast<uint8_t>((t1 | t2) & 0xFF));

        t1 = (static_cast<uint16_t>(sv[1]) - 32) << 4;
        t2 = (static_cast<uint16_t>(sv[2]) - 32) >> 2;
        rv.push_back(static_cast<uint8_t>((t1 | t2) & 0xFF));

        t1 = (static_cast<uint16_t>(sv[2]) - 32) << 6;
        t2 = (static_cast<uint16_t>(sv[3]) - 32);
        rv.push_back(static_cast<uint8_t>((t1 | t2) & 0xFF));

        sv = sv.substr(4);
    }
    return rv;
}
} // end namespace easyUtils
