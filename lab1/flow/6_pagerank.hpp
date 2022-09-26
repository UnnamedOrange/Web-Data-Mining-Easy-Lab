#pragma once

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

#include <global.hpp>

namespace flow
{
    using real_t = double;

    /**
     * @brief PageRank.
     */
    bool pagerank()
    {
        // Print.
        std::cout << "6. PageRank." << std::endl;

        // Parameters.
        constexpr size_t n_epoch = 100;
        constexpr real_t damping_factor = 0.85; // alpha.

        // Rank.
        std::vector<real_t> rank(global::node_names.size(), real_t(1));

        // Iterate.
        for (size_t epoch = 0; epoch < n_epoch; epoch++)
        {
            std::vector<real_t> new_rank(global::node_names.size());
            for (size_t i = 0; i < global::node_names.size(); i++)
            {
                real_t sum = 0;
                const auto& inlink = global::graph.edges_backward[i];
                for (size_t j_idx = 0; j_idx < inlink.size(); j_idx++)
                {
                    size_t j = inlink[j_idx];
                    const auto& outlink = global::graph.edges_forward[j];
                    sum += rank[j] / outlink.size(); // outlink.size() is not 0.
                }
                new_rank[i] = (1 - damping_factor) + damping_factor * sum;
            }

            // Output the norm.
            real_t norm = 0;
            for (size_t i = 0; i < global::node_names.size(); i++)
                norm += (new_rank[i] - rank[i]) * (new_rank[i] - rank[i]);
            norm = std::sqrt(norm);
            std::cout << "Epoch " << epoch << ": norm = " << norm << std::endl;

            rank = std::move(new_rank);
        }

        // Print the top 10.
        std::vector<std::pair<real_t, size_t>> rank_with_idx;
        for (size_t i = 0; i < global::node_names.size(); i++)
            rank_with_idx.emplace_back(rank[i], i);
        std::stable_sort(
            rank_with_idx.begin(), rank_with_idx.end(),
            [](const auto& a, const auto& b) { return a.first > b.first; });
        std::cout << "Top 10:" << std::endl;
        for (size_t i = 0; i < 10; i++)
        {
            std::cout << global::node_names[rank_with_idx[i].second] << ": "
                      << rank_with_idx[i].first << std::endl;
        }

        // Output to file.
        std::ofstream ofs(global::working_dir / "pagerank.txt");
        for (const auto& [r, i] : rank_with_idx)
            ofs << global::node_names[i] << "\t" << r << std::endl;
        std::cout << "Output to " << (global::working_dir / "pagerank.txt")
                  << std::endl;

        return true;
    }
} // namespace flow
