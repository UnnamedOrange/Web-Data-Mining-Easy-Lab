#pragma once

#include <algorithm>
#include <filesystem>
#include <optional>
#include <random>

#include <global.hpp>
#include <parser/index.hpp>

namespace flow
{
    /**
     * @brief Enumerate all indices and store them in global::index_list.
     */
    inline bool load_indices()
    {
        // Print.
        std::cout << "1. Load indices." << std::endl;

        // Enumerate the index files.
        std::vector<std::filesystem::path> index_files;
        for (auto& p : std::filesystem::recursive_directory_iterator(
                 global::working_dir))
            if (p.path().u16string().find(u"index") != std::u16string::npos)
                index_files.push_back(p.path());
        std::sort(index_files.begin(), index_files.end());

        // Parse each index file.
        for (const auto& file : index_files)
        {
            std::cout << "Parsing " << file << "..." << std::endl;

            parser::index_parser p;
            p.open(file.string());

            while (true)
            {
                auto index = p.next();
                if (!index)
                    break;
                global::index_list.push_back(*index);
            }
        }

        // Output the result.
        std::cout << global::index_list.size() << " indices found."
                  << std::endl;

        // Sort the index list.
        std::cout << "Sorting index list..." << std::endl;
        std::sort(global::index_list.begin(), global::index_list.end());

        // Print some examples.
        std::random_device rd;
        std::default_random_engine e(rd());
        std::uniform_int_distribution<size_t> u(0,
                                                global::index_list.size() - 1);
        std::cout << "Some examples: ";
        for (size_t i = 0; i < 10; ++i)
            std::cout << global::index_list[u(e)] << "; ";
        std::cout << std::endl;

        std::cout << std::endl;
        return true;
    }
} // namespace flow
