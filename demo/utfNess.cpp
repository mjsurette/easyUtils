
#include "utfNess.h"
using namespace easyUtils;

#include <fstream>
#include <iostream>
using namespace std;

constexpr int BUFSIZE = 1024;

//==============================================================================
int main(int argc, char *argv[])
{
    cout << "utfNess" << endl;
    for (int i = 1; i < argc; ++i)
    {
        std::ifstream is(argv[i], std::ifstream::binary);
        if (is)
        {
            is.seekg(0, is.end);
            int length = is.tellg();
            is.seekg(0, is.beg);

            char buf[BUFSIZE];
            is.read(buf, BUFSIZE);
            auto utfType = utfNess(string_view(buf, is.gcount()));

            cout << argv[i] << '\t' << length << '\t';

            switch (utfType)
            {
            case UTFness::UTF8wBOM:
                cout << " utf8 with BOM" << endl;
                break;
            case UTFness::LEwBOM:
                cout << " little endian with BOM" << endl;
                break;
            case UTFness::BEwBOM:
                cout << " big endian with BOM" << endl;
                break;
            case UTFness::UTF8:
                cout << " utf8 no BOM" << endl;
                break;
            case UTFness::LE:
                cout << " little endian no BOM" << endl;
                break;
            case UTFness::BE:
                cout << " big endian no BOM" << endl;
                break;
            }
        }
    }
    return 0;
}
