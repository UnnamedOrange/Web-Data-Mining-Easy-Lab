#pragma once

#include <chrono>
#include <iostream>

#include <global.hpp>
#include <parser/page_parser.hpp>
#include <parser/page_t.hpp>

namespace flow
{
    /**
     * @brief Load raw pages and store them in global::page_list.
     */
    inline bool load_pages()
    {
        // Print.
        std::cout << "1. Load pages." << std::endl;

        // Perf. counter.
        auto start = std::chrono::high_resolution_clock::now();

        // Load pages.
        parser::page_parser parser;
        parser.open(global::working_dir / "wiki.csv");
        while (auto page = parser.next())
            global::page_list.push_back(*page);

        // Output results.
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << global::page_list.size() << " pages loaded in "
                  << elapsed.count() << " ms." << std::endl;

        std::cout << std::endl;
        return true;
    }
} // namespace flow
