
#include "catch.hpp"

#include "uuencode.h"
using namespace easyUtils;

#include <string_view>
using namespace std;

//==============================================================================
TEST_CASE("basic lookup test")
{
    auto encoded = uuencode(string_view("Cat"));
    REQUIRE(encoded == "0V%T");

    auto decoded = uudecode(encoded);
    auto sv
        = string_view(reinterpret_cast<char *>(decoded.data()), decoded.size());
    REQUIRE(sv == "Cat");
}
