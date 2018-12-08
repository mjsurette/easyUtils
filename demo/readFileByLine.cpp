
#include "readFileAsUTF8.h"
using namespace easyUtils;

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        auto fileName = argv[i];
        cerr << fileName << endl;
        auto fileText = ReadFileAsUTF8(fileName);
        for (auto const &line : fileText)
            cout << line << '\n';
    }
}
