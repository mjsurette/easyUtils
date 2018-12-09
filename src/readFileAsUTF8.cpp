#include "readFileAsUTF8.h"
#include "utfConvert.h"
#include "utfNess.h"

#include <fstream>

namespace easyUtils
{
using namespace std;

//==============================================================================
constexpr int BUFSIZE = 1024;

ReadFileAsUTF8::ReadFileAsUTF8(std::string const &fileName)
    : _lineCount(0)
{
    ifstream ifs;
    ifs.exceptions(ifstream::badbit);
    ifs.open(fileName, ios::in | ios::binary);

    string buffer(BUFSIZE, '\0');
    ifs.read(buffer.data(), BUFSIZE);

    auto fileType = utfNess(
        string_view(buffer.data(), static_cast<unsigned>(ifs.gcount())));
    if (fileType == UTFness::UTF8wBOM || fileType == UTFness::UTF8)
        readUTF8(ifs, fileType);
    else
        readUTF16(ifs, fileType);

    string_view svLines(_data);
    while (svLines.size() > 0)
    {
        ++_lineCount;
        auto pos = svLines.find_first_of("\r\n");
        if (pos == svLines.npos)
        {
            svLines = string_view();
        }
        else
        {
            if (svLines[pos] == '\r' && svLines.size() > pos
                && svLines[pos + 1] == '\n')
            {
                ++pos;
            }
            svLines = svLines.substr(pos + 1);
        }
    }
}

//==============================================================================
void ReadFileAsUTF8::readUTF8(std::ifstream &ifs, UTFness fileType)
{
    ifs.seekg(0, ifs.end);
    auto length = ifs.tellg();

    if (fileType == UTFness::UTF8wBOM)
    {
        ifs.seekg(3, ifs.beg);
        length -= 3;
    }
    else
    {
        ifs.seekg(0, ifs.beg);
    }
    _data = string(length, '\0');
    ifs.read(&_data[0], length);
}

//==============================================================================
void ReadFileAsUTF8::readUTF16(std::ifstream &ifs, UTFness fileType)
{
    ifs.seekg(0, ifs.end);
    auto length = ifs.tellg();
    _data.reserve(length);

    if (fileType == UTFness::LEwBOM || fileType == UTFness::BEwBOM)
    {
        ifs.seekg(2, ifs.beg);
        length -= 2;
    }
    else
    {
        ifs.seekg(0, ifs.beg);
    }

    string inData;
    string_view sv;

    while (!ifs.eof() || sv.size() > 0)
    {
        if (sv.size() < 2 && !ifs.eof())
        {
            string tmp(sv);
            string buffer(BUFSIZE, '\0');
            ifs.read(buffer.data(), BUFSIZE);
            buffer.resize(ifs.gcount());

            if (fileType == UTFness::BEwBOM || fileType == UTFness::BE)
                for (size_t i = 0; i < buffer.size(); i += 2)
                    std::swap(buffer[i], buffer[i + 1]);

            inData = tmp + buffer;
            sv = string_view(inData);
        }
        // convert UTF-16 to UTF8
        unsigned n;
        CodePoint cp;
        tie(cp, n) = le2cp(sv);
        _data += cp2string(cp);
        sv = sv.substr(n);
    }
    _data.shrink_to_fit();
}

//==============================================================================
void ReadFileAsUTF8::iterator::nextLine() noexcept
{
    constexpr string_view terminator("\r\n");
    if (_ixNextLine > _data.size())
    {
        lastLine();
    }
    else
    {
        auto first = _ixNextLine;
        auto last = _data.find_first_of(terminator, _ixNextLine);
        if (last == string_view::npos)
        {
            lastLine();
        }
        else
        {
            auto lpos = last + 1;
            if (_data[last] == '\r' && last < (_data.size() - 1)
                && _data[last + 1] == '\n')
                ++lpos;
            _ixNextLine = lpos;
            _current = _data.substr(first, last - first);
        }
    }
}

//==============================================================================
void ReadFileAsUTF8::iterator::lastLine() noexcept
{
    _ixNextLine = _data.size() + 1;
    _current = string_view("");
}

} // end namespace easyUtils
