#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include <global.hpp>
#include <parser/page.hpp>

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
                 global::working_dir))
            if (p.path().u16string().find(u"index") == std::u16string::npos)
                page_files.push_back(p.path());
        std::sort(page_files.begin(), page_files.end());

        // Parse each page file.
        global::page_list.reserve(1496606);
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
                global::page_list.push_back(std::move(*page));
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

        // Compare pages with links.
        if constexpr (false)
        {
            std::unordered_set<std::string> page_set;
            page_set.reserve(1496606);
            for (const auto& page : global::page_list)
                page_set.insert(page.title);
            std::cout << "Found " << page_set.size()
                      << " unique pages in page list." << std::endl;

            std::unordered_set<std::string> link_set;
            link_set.reserve(14319445);
            size_t n_link{};
            for (const auto& page : global::page_list)
                n_link += page.links.size();
            link_set.reserve(n_link);
            for (const auto& page : global::page_list)
                for (const auto& link : page.links)
                    link_set.insert(link);
            std::cout << n_link << " links found, " << link_set.size()
                      << " unique links found." << std::endl;

            size_t found_in_page{};
            for (const auto& link : link_set)
                found_in_page += page_set.count(link);
            std::cout << "Found " << found_in_page << " links in pages."
                      << std::endl;

            size_t found_in_link{};
            for (const auto& page : page_set)
                found_in_link += link_set.count(page);
            std::cout << "Found " << found_in_link << " pages in links."
                      << std::endl;
        }

        std::cout << std::endl;
        return true;
    }
} // namespace flow
