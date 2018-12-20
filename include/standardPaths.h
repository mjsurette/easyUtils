#pragma once

#include <filesystem>
#include <string_view>

namespace easyUtils
{
std::filesystem::path myHome();

std::filesystem::path myConfig(std::string_view appName = std::string_view());
std::filesystem::path myData(std::string_view appName = std::string_view());
std::filesystem::path myDesktop();
std::filesystem::path myDocuments();
std::filesystem::path myDownloads();
std::filesystem::path myMusic();
std::filesystem::path myPictures();
std::filesystem::path myVideos();

} // end namespace easyUtils
