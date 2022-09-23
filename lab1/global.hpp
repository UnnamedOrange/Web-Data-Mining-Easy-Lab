#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <parser/page.hpp>

namespace global
{
    // Configurations.
    inline std::filesystem::path working_path;

    // Raw data.
    inline std::vector<std::string> index_list;
    inline std::vector<page_t> page_list;
} // namespace global
