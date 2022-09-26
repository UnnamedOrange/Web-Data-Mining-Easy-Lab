#pragma once

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include <global.hpp>

namespace flow
{
    /**
     * @brief Get some basic information about the graph.
     */
    bool analyze_graph()
    {
        // Print.
        std::cout << "5. Analyze the graph." << std::endl;

        // Degree.
        {
            size_t max_in_degree = 0;
            size_t min_in_degree = std::numeric_limits<size_t>::max();
            size_t sum_in_degree = 0;
            for (const auto& node : global::graph.edges_backward)
            {
                size_t degree = node.size();
                max_in_degree = std::max(max_in_degree, degree);
                min_in_degree = std::min(min_in_degree, degree);
                sum_in_degree += degree;
            }

            size_t max_out_degree = 0;
            size_t min_out_degree = std::numeric_limits<size_t>::max();
            size_t sum_out_degree = 0;
            for (const auto& node : global::graph.edges_forward)
            {
                size_t degree = node.size();
                max_out_degree = std::max(max_out_degree, degree);
                min_out_degree = std::min(min_out_degree, degree);
                sum_out_degree += degree;
            }

            std::cout << "In degree: " << min_in_degree << " ~ "
                      << max_in_degree << ", average: "
                      << (double)sum_in_degree /
                             global::graph.edges_backward.size()
                      << std::endl;
            std::cout << "Out degree: " << min_out_degree << " ~ "
                      << max_out_degree << ", average: "
                      << (double)sum_out_degree /
                             global::graph.edges_forward.size()
                      << std::endl;
        }

        // The number of weakly connected component.
        {
            std::vector<bool> visited(global::graph.edges_backward.size());
            size_t component_count = 0;
            for (size_t i = 0; i < visited.size(); ++i)
            {
                if (visited[i])
                    continue;
                ++component_count;
                std::vector<size_t> stack;
                stack.push_back(i);
                while (!stack.empty())
                {
                    size_t node = stack.back();
                    stack.pop_back();
                    visited[node] = true;
                    for (size_t neighbor : global::graph.edges_forward[node])
                        if (!visited[neighbor])
                            stack.push_back(neighbor);
                    for (size_t neighbor : global::graph.edges_backward[node])
                        if (!visited[neighbor])
                            stack.push_back(neighbor);
                }
            }
            std::cout << "The number of weakly connected component: "
                      << component_count << std::endl;
        }

        std::cout << std::endl;
        return true;
    }
} // namespace flow
