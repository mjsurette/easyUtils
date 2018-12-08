
#include "utfNess.h"

namespace easyUtils
{
UTFness utfNess(std::string_view buffer) noexcept
{
    if (buffer.size() < 2)
        return UTFness::UTF8;
    if (buffer.size() % 2 == 1)
        return UTFness::UTF8;
    // check for BOM
    unsigned char l, r, o;
    l = buffer[0];
    r = buffer[1];
    if (l == 0xFF && r == 0xFE)
        return UTFness::LEwBOM;
    if (l == 0xFE && r == 0xFF)
        return UTFness::BEwBOM;
    if (buffer.size() > 2)
    {
        o = buffer[2];
        if (l == 0xEF && r == 0xBB && o == 0xBF)
            return UTFness::UTF8wBOM;
    }
    // no BOM --- use heuristics
    int lcount = 0, rcount = 0;

    auto it = buffer.begin();
    while (it != buffer.end())
    {
        if (*it++ == 0)
            ++lcount;
        if (*it++ == 0)
            ++rcount;
    }
    if (lcount / 2 > rcount)
        return UTFness::LE;
    if (rcount / 2 > lcount)
        return UTFness::BE;

    return UTFness::UTF8;
}

} // end namespace easyUtils
