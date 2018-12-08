#pragma once

// unicode codepoint info from
//  http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=iws-appendixa

#include <cstdint>
#include <string_view>
#include <tuple>

namespace easyUtils
{
using CodePoint = uint32_t;

//==============================================================================
// takes in a little endian encoded stream of bytes as a std::string_view
// throws std::domain_error on invalid input
std::tuple<CodePoint, unsigned> le2cp(std::string_view svIn);

//==============================================================================
// throws std::domain_error on invalid input
std::string cp2string(CodePoint const &cp);

} // end namespace easyUtils
