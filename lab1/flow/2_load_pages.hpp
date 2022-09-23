#pragma once

#include <unordered_set>

namespace flow
{
    /**
     * @brief Enumerate all pages and store them in global::page_list.
     */
    inline bool load_pages()
    {
        // Print.
        std::cout << "2. Load pages." << std::endl;

        // Enumerate the page files.
        std::vector<std::filesystem::path> page_files;
        for (auto& p : std::filesystem::recursive_directory_iterator(
                 global::working_path))
            if (p.path().u16string().find(u"index") == std::u16string::npos)
                page_files.push_back(p.path());
        std::sort(page_files.begin(), page_files.end());

        // Parse each page file.
        for (const auto& file : page_files)
        {
            std::cout << "Parsing " << file << "..." << std::endl;

            parser::page_parser p;
            p.open(file.string());

            while (true)
            {
                auto page = p.next();
                if (!page)
                    break;
                global::page_list.push_back(*page);
            }
        }

        // Output the result.
        std::cout << global::page_list.size() << " pages found." << std::endl;

        // Print some examples.
        std::random_device rd;
        std::default_random_engine e(rd());
        std::uniform_int_distribution<size_t> u(0,
                                                global::page_list.size() - 1);
        std::cout << "Some examples: ";
        for (size_t i = 0; i < 10; ++i)
            std::cout << global::page_list[u(e)].title << "; ";
        std::cout << std::endl;

        // Compare pages with indices.
        if constexpr (false)
        {
            std::unordered_set<std::string> index_set;
            index_set.reserve(global::index_list.size());
            for (const auto& index : global::index_list)
                index_set.insert(index);

            size_t found_in_index{};
            for (const auto& page : global::page_list)
                found_in_index += index_set.count(page.title);
            std::cout << "Found " << found_in_index << " pages in index."
                      << std::endl;
        }

        std::cout << std::endl;
        return true;
    }
} // namespace flow
