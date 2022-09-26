#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

namespace graph
{
    class name_map
    {
        std::vector<std::string> names;

    public:
        void clear() { names.clear(); }
        void append(const std::string& str) { names.push_back(str); }
        void sort()
        {
            std::sort(names.begin(), names.end());
            names.erase(std::unique(names.begin(), names.end()), names.end());
            names.shrink_to_fit();
        }
        size_t size() const { return names.size(); }
        size_t find(std::string_view str) const
        {
            return std::lower_bound(names.begin(), names.end(), str) -
                   names.begin();
        }

    public:
        void save(const std::filesystem::path& path) const
        {
            std::ofstream ofs(path);
            for (const auto& name : names)
                ofs << name << '\n';
        }
        void load(const std::filesystem::path& path)
        {
            std::vector<std::string> new_names;

            std::ifstream ifs(path);
            std::string str;
            while (std::getline(ifs, str))
            {
                if (str.empty())
                    continue;
                new_names.push_back(str);
            }
            names.swap(new_names);
        }
    };
} // namespace graph
