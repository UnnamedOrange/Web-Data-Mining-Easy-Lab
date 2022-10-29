#pragma once

#include <filesystem>
#include <vector>

#include <parser/page_t.hpp>

namespace global
{
    // Configurations.
    inline std::filesystem::path working_dir;

    // Raw.
    inline std::vector<page_t> page_list;
} // namespace global
