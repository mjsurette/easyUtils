#pragma once

#include <array>
#include <map>
#include <set>
#include <string>
#include <string_view>

namespace easyUtils
{

//==============================================================================
template <typename T, std::size_t N> class TextMap
{
private:
    std::array<std::string_view, N> _text;

public:
    template <typename... Args>
    constexpr explicit TextMap(Args... args)
        : _text { args... }
    {
    }

    //==============================================================================
    constexpr int textMap(std::string_view val) const
    {
        for(int i = 0; i < static_cast<int>(_text.size()); ++i)
        {
            const std::string_view &v = _text[i];
            if(val == v)
                return static_cast<int>(i);
        }
        return -1;
    }

    //==============================================================================
    std::set<std::string> findDups() const
    {
        std::set<std::string> dups;
        std::multimap<std::string_view, size_t> m;

        for(size_t i = 0; i < _text.size(); ++i)
            m.emplace(std::make_pair(_text[i], i));

        for(auto v : m)
            if(m.count(v.first) > 1)
                dups.insert(std::string(v.first));
        return dups;
    }
};

//==============================================================================
template <typename... Args>
explicit TextMap(Args... args)
    ->TextMap<std::common_type_t<Args...>, sizeof...(Args)>;

} // end namespace easyUtils
