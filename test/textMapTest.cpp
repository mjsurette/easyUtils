
#include "catch.hpp"

#include "textMap.h"
using namespace easyUtils;

#include <string_view>
using namespace std;

//==============================================================================
constexpr TextMap tm{ "one", "two", "three" };
constexpr auto operator"" _tmap(const char *val, long unsigned int)
{
    return tm.textMap(val);
}

//==============================================================================
TEST_CASE("basic lookup test")
{
    REQUIRE(tm.textMap("one") == 0);
    REQUIRE(tm.textMap("two") == 1);
    REQUIRE(tm.textMap("three") == 2);
    REQUIRE(tm.textMap("four") == -1);
}

//==============================================================================
TEST_CASE("user literal test")
{
    REQUIRE("one"_tmap == 0);
    REQUIRE("two"_tmap == 1);
    REQUIRE("three"_tmap == 2);
    REQUIRE("four"_tmap == -1);
}

//==============================================================================
TEST_CASE("switch test")
{
    for (auto &cv : { "one", "two", "three", "four" })
    {
        auto v = tm.textMap(cv);

        switch (v)
        {
        case tm.textMap("one"):
            REQUIRE(v == 0);
            break;
        case tm.textMap("two"):
            REQUIRE(v == 1);
            break;
        case tm.textMap("three"):
            REQUIRE(v == 2);
            break;
        default:
            REQUIRE(v == -1);
        }
    }
}

//==============================================================================
TEST_CASE("find duplicates")
{
    REQUIRE(tm.findDups().size() == 0);

    TextMap tm2{ "one", "two", "three", "two" };
    REQUIRE(tm2.findDups().size() == 1);

    auto it = tm2.findDups().begin();
    REQUIRE(*it == "two");
}

//==============================================================================
/* from top of this file for reference
constexpr TextMap tm{ "one", "two", "three" };
constexpr auto operator"" _tmap(const char *val, long unsigned int)
{
    return tm.textMap(val);
}

    note that v is evaluated at run time
    but each case value is evaluated at compile time
*/
TEST_CASE("switch & user literal test")
{
    for (auto &cv : { "one", "two", "three", "four" })
    {
        auto v = tm.textMap(cv);

        switch (v)
        {
        case "one"_tmap:
            REQUIRE(v == 0);
            break;
        case "two"_tmap:
            REQUIRE(v == 1);
            break;
        case "three"_tmap:
            REQUIRE(v == 2);
            break;
        default:
            REQUIRE(v == -1);
        }
    }
}
