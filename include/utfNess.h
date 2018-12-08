#pragma once

#include <string_view>

namespace easyUtils
{
//==============================================================================
enum class UTFness
{
    UTF8wBOM,
    LEwBOM,
    BEwBOM,
    UTF8,
    LE,
    BE
};

//==============================================================================
UTFness utfNess(std::string_view buffer) noexcept;

} // end namespace easyUtils
