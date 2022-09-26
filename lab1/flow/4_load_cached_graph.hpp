#pragma once

#include <iostream>

#include <global.hpp>

namespace flow
{
    /**
     * @brief Load cached graph.
     * - node_names.txt
     * - graph.dat
     */
    inline bool load_cached_graph()
    {
        // Print.
        std::cout << "4. Load cached graph." << std::endl;

        // Load the node names.
        global::node_names.load(global::working_path / "node_names.txt");
        std::cout << "Loaded " << global::node_names.size() << " node names."
                  << std::endl;

        // Load the graph.
        global::graph.load(global::working_path / "graph.dat");
        std::cout << "Loaded " << global::graph.size() << " edges."
                  << std::endl;

        // Build the graph.
        std::cout << "Building the graph..." << std::endl;
        global::graph.build_graph(global::node_names.size());

        std::cout << std::endl;
        return true;
    }
} // namespace flow
