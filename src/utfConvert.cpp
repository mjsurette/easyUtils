#include "utfConvert.h"

// unicode codepoint info from
//  http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=iws-appendixa

#include <stdexcept>
#include <string>
using namespace std;

namespace easyUtils
{

//==============================================================================
std::tuple<CodePoint, unsigned> le2cp(std::string_view svIn)
{
    CodePoint rv, cp1, cp2;

    if (svIn.size() < 2)
        throw std::domain_error("unexpected end of input in utf16_2cp");

    unsigned char c0, c1, c2, c3;
    c0 = static_cast<unsigned char>(svIn[0]);
    c1 = static_cast<unsigned char>(svIn[1]);
    cp1 = static_cast<CodePoint>(c1) << 8 | static_cast<CodePoint>(c0);

    if (cp1 <= 0xD7FF || (cp1 >= 0xE000 && cp1 <= 0xEFFF))
    { // 00000 xxxx xxxx xxxx xxxx <<= xxxx xxxx xxxx xxxx
        return { cp1, 2 };
    }
    else if ((cp1 & 0xFC00) == 0xD800)
    { // uuuu xxxx xxyy yyyy yyyy <<= 1101 10ww wwxx xxxx 1101 11yy yyyy yyyy
        //(where uuuuu = wwww + 1)
        if (svIn.size() < 4)
            throw std::domain_error("unexpected end of input in utf16_2cp");

        c2 = static_cast<unsigned char>(svIn[2]);
        c3 = static_cast<unsigned char>(svIn[3]);
        cp2 = static_cast<CodePoint>(c3) << 8 | static_cast<CodePoint>(c2);

        if ((cp2 & 0xFC00) != 0xDC00)
            throw std::domain_error("invalid input to utf16_2cp - !0xDC ");

        CodePoint u, w, x, y;
        w = (cp1 >> 6) & 0xFF;
        x = cp1 & 0xFFF;
        y = cp2 & 0xFFFFF;
        u = w + 1;

        rv = y | (x << 10) | (u << 16);
        return { rv, 2 };
    }
    else
    {
        throw std::domain_error(
            "invalid input to utf16_2cp "s + to_string(svIn.size()));
    }
}

//==============================================================================
std::string cp2string(CodePoint const &cp)
{
    std::string rv;
    unsigned u, x, y, z;

    if (cp < 0x7F)
    {
        rv += static_cast<char>(cp);
    }
    else if (cp > 0x7F && cp <= 0x7FF)
    { // 0000000000 yyyyy xxxxxx ==> 110yyyyy 10xxxxxx
        x = cp & 0x3F;
        y = cp >> 6 & 0x1F;
        rv += static_cast<char>(0xC0 | y);
        rv += static_cast<char>(0x80 | x);
    }
    else if ((cp >= 0x800 && cp <= 0xD7FF) || (cp >= 0xE000 && cp <= 0xFFFF))
    { // 00000 zzzz yyyyyy xxxxxx ==> 1110zzzz 10yyyyyy	10xxxxxx
        x = cp & 0x3F;
        y = (cp >> 6) & 0x3F;
        z = (cp >> 12) & 0xF;
        rv += static_cast<char>(0xE0 | z);
        rv += static_cast<char>(0x80 | y);
        rv += static_cast<char>(0x80 | x);
    }
    else if (cp >= 0x1'0000 && cp <= 0x11'0000)
    { // uuu zzzzzz yyyyyy xxxxxx ==> 11110uuu	10zzzzzz 10yyyyyy 10xxxxxx
        x = cp & 0x3F;
        y = (cp >> 6) & 0x3F;
        z = (cp >> 12) & 0x3F;
        u = (cp >> 18) & 0x7;
        rv += static_cast<char>(0xF0 | u);
        rv += static_cast<char>(0x80 | z);
        rv += static_cast<char>(0x80 | y);
        rv += static_cast<char>(0x80 | x);
    }
    else
    {
        throw std::domain_error("invalid input to cp2string");
    }
    return rv;
}

} // end namespace easyUtils
