#pragma once

#include <iostream>

#include <global.hpp>

namespace flow
{
    /**
     * @brief Sample 2000 pages.
     */
    inline bool sample_pages()
    {
        // Print.
        std::cout << "2. Sample pages." << std::endl;

        // Sample pages.
        global::page_list.resize(2000);
        global::page_list.shrink_to_fit();

        std::cout << std::endl;
        return true;
    }
} // namespace flow
