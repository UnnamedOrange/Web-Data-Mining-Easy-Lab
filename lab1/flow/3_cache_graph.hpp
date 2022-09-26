#pragma once

#include <iostream>

#include <global.hpp>
#include <graph/graph.hpp>
#include <graph/name_map.hpp>

namespace flow
{
    /**
     * @brief Cache the graph into files.
     * - node_names.txt: A list of titles, one title per line.
     * - graph.dat: A list of edges, each edge takes 8 bytes.
     */
    inline bool cache_graph()
    {
        // Print.
        std::cout << "3. Cache graph." << std::endl;

        // Build the name map.
        std::cout << "Building the name map..." << std::endl;
        global::node_names.clear();
        for (const auto& page : global::page_list)
            global::node_names.append(page.title);
        global::node_names.sort();

        // Backup the links. This takes a long time.
        if constexpr (false)
        {
            std::cout << "Building the link name map..." << std::endl;
            graph::name_map link_names;
            for (const auto& page : global::page_list)
                for (const auto& link : page.links)
                    link_names.append(link);
            link_names.sort();
            link_names.save("link_names.txt");
        }

        // Build the graph.
        std::cout << "Building the graph..." << std::endl;
        global::graph.clear();
        for (const auto& page : global::page_list)
            for (const auto& link : page.links)
            {
                graph::node_t to = global::node_names.find(link);
                if (to == global::node_names.size())
                    continue;
                graph::node_t from = global::node_names.find(page.title);
                global::graph.append({from, to});
            }
        global::graph.sort();
        global::graph.build_graph(global::node_names.size());

        // Save.
        global::node_names.save("node_names.txt");
        global::graph.save("graph.dat");
        std::cout << "Cache saved." << std::endl;

        // Output the result.
        std::cout << global::node_names.size() << " nodes found." << std::endl;
        std::cout << global::graph.size() << " edges found." << std::endl;

        std::cout << std::endl;
        return true;
    }
} // namespace flow
