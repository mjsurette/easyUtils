
#include "textMap.h"
using namespace easyUtils;

#include <iostream>
#include <string_view>
using namespace std;

//==============================================================================
int main()
{
    constexpr TextMap tm { "one", "two", "three" };

    for(auto cv : { "one", "two", "three", "four" })
    {
        auto v = tm.textMap(cv);

        switch(v)
        {
        case tm.textMap("one"):
            cout << "OK " << cv << endl;
            break;
        case tm.textMap("two"):
            cout << "OK " << cv << endl;
            break;
        case tm.textMap("three"):
            cout << "OK " << cv << endl;
            break;
        default:
            cout << "OK " << cv << ' ' << tm.textMap(cv) << endl;
        }
    }
}
