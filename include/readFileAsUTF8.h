#pragma once

#include "utfNess.h"

#include <string>
#include <string_view>

namespace easyUtils
{
//==============================================================================
/*
*! throws std::ios_base::failure on error when opening or reading a file
*! throws domain error with odd # of bytes on UTF-16 file
*/
class ReadFileAsUTF8
{
    // iterates over data line by line
    class iterator
    //        : public std::iterator<std::forward_iterator_tag, ReadFileAsUTF8>
    {
        friend class ReadFileAsUTF8;

    public:
        using value_type = ReadFileAsUTF8;
        using reference = ReadFileAsUTF8&;
        using iterator_category = std::forward_iterator_tag;
        using pointer = ReadFileAsUTF8 *;
        using difference_type = void;

        // standard constructors
        iterator() = delete;
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        ~iterator() = default;
        //  custom constructor
        explicit iterator(ReadFileAsUTF8 const &r)
            : _data(r._data)
            , _ixNextLine(0)
        {
        }

        // operators
        iterator operator++() noexcept
        {
            nextLine();
            return *this;
        }

        iterator operator++(int) noexcept
        {
            iterator tmp(*this);
            nextLine();
            return tmp;
        }

        bool operator==(iterator const &rhs) const noexcept
        {
            return _ixNextLine == rhs._ixNextLine
                && _current == rhs._current
                && _data == rhs._data;
        }

        bool operator!=(iterator const &rhs) const noexcept
        {
            return _ixNextLine != rhs._ixNextLine
                || _current != rhs._current
                || _data != rhs._data;
        }

        std::string_view operator*()
        {
            return _current;
        }

    private:
        std::string_view _data;
        std::string_view _current;
        size_t _ixNextLine;

        void nextLine() noexcept;
        void lastLine() noexcept;
    }; // end class iterator

    // back to ReadFileAsUTF8
public:
    // standard constructors
    ReadFileAsUTF8() = delete;
    ReadFileAsUTF8(const ReadFileAsUTF8 &) = default;
    ReadFileAsUTF8(ReadFileAsUTF8 &&) = default;
    ReadFileAsUTF8 &operator=(const ReadFileAsUTF8 &) = default;
    ReadFileAsUTF8 &operator=(ReadFileAsUTF8 &&) = default;
    ~ReadFileAsUTF8() = default;
    //  custom constructor
    explicit ReadFileAsUTF8(std::string const &fileName);

    std::string_view data() const noexcept
    {
        return _data;
    };

    auto size() const noexcept
    {
        return _data.size();
    };

    auto lineCount() const noexcept
    {
        return _lineCount;
    };

    iterator begin() noexcept
    {
        iterator rv(*this);
        rv.nextLine();
        return rv;
    }

    iterator end() noexcept
    {
        iterator rv(*this);
        rv.lastLine();
        return rv;
    }

private:
    std::string _data;
    size_t _lineCount;

    void readUTF8(std::ifstream &ifs, UTFness fileType);
    void readUTF16(std::ifstream &ifs, UTFness fileType);
}; // end class ReadFileAsUTF8

} // end namespace easyUtils
