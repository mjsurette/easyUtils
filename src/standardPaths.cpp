
#include "standardPaths.h"

#include <cstdlib>
#include <string>
using namespace std;

namespace easyUtils
{
//==============================================================================
std::filesystem::path myHome()
{
#ifdef _WIN32
    string path(getenv("USERPROFILE"));
    for (auto &ch : path)
        if (ch == '\\')
            ch = '/';
    return std::filesystem::path(path);
#else
    return std::filesystem::path(getenv("HOME"));
#endif
}

//==============================================================================
std::filesystem::path myConfig(std::string_view appName)
{
#ifdef _WIN32
    return myHome() / "AppData/Local" / appName;
#elif __APPLE__
    return myHome() / "Library/Preferences" / appName;
#else
    return myHome() / ".config" / appName;
#endif
}

//==============================================================================
std::filesystem::path myDesktop()
{
    return myHome() / "Desktop";
}

//==============================================================================
std::filesystem::path myData(std::string_view appName)
{
#ifdef _WIN32
    return myHome() / "AppData/Local" / appName;
#elif __APPLE__
    return myHome() / "Support" / appName;
#else
    // Support
    return myHome() / ".local/share" / appName;
#endif
}

//==============================================================================
std::filesystem::path myDocuments()
{
    return myHome() / "Documents";
}

//==============================================================================
std::filesystem::path myDownloads()
{
    return myHome() / "Downloads";
}

//==============================================================================
std::filesystem::path myMusic()
{
    return myHome() / "Music";
}

//==============================================================================
std::filesystem::path myPictures()
{
    return myHome() / "Pictures";
}

//==============================================================================
std::filesystem::path myVideos()
{
    return myHome() / "Videos";
}
} // end namespace easyUtils
