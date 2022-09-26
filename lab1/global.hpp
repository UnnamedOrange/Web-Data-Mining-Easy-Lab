#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <graph/graph.hpp>
#include <graph/name_map.hpp>
#include <parser/page.hpp>

namespace global
{
    // Configurations.
    inline std::filesystem::path working_dir;

    // Raw data.
    inline std::vector<std::string> index_list;
    inline std::vector<page_t> page_list;

    // Graph.
    inline graph::name_map node_names;
    inline graph::graph_t graph;
} // namespace global
