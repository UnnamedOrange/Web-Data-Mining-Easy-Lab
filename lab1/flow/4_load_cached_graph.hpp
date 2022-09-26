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

        // Print some examples.
        std::random_device rd;
        std::default_random_engine e(rd());
        std::uniform_int_distribution<size_t> u(0, global::graph.size() - 1);
        std::cout << "Some examples: ";
        for (size_t i = 0; i < 10; ++i)
        {
            const auto& edge = global::graph.raw_edges[u(e)];
            std::cout << global::node_names[edge.from] << " -> "
                      << global::node_names[edge.to] << "; ";
        }
        std::cout << std::endl;

        std::cout << std::endl;
        return true;
    }
} // namespace flow
