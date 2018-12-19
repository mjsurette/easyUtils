
#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace easyUtils
{
//==============================================================================
std::string uuencode(std::string_view sv);
std::vector<uint8_t> uudecode(std::string_view sv);

} // end namespace easyUtils
