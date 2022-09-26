#pragma once

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

namespace graph
{
    using node_t = uint32_t;

    struct edge_t
    {
        node_t from;
        node_t to;
        bool operator<(const edge_t& rhs) const
        {
            return from < rhs.from || (from == rhs.from && to < rhs.to);
        }
        bool operator==(const edge_t& rhs) const
        {
            return from == rhs.from && to == rhs.to;
        }
    };

    class graph_t
    {
    private:
        std::vector<edge_t> raw_edges;
        std::vector<std::vector<node_t>> _edges_forward;
        std::vector<std::vector<node_t>> _edges_backward;

    public:
        const std::vector<std::vector<node_t>>& edges_forward{_edges_forward};
        const std::vector<std::vector<node_t>>& edges_backward{_edges_backward};

    public:
        void clear()
        {
            raw_edges.clear();
            _edges_forward.clear();
            _edges_backward.clear();
        }
        void append(const edge_t& edge) { raw_edges.push_back(edge); }
        void sort()
        {
            std::sort(raw_edges.begin(), raw_edges.end());
            raw_edges.erase(std::unique(raw_edges.begin(), raw_edges.end()),
                            raw_edges.end());
            raw_edges.shrink_to_fit();
        }
        void build_graph(size_t n_node)
        {
            sort();

            _edges_forward.clear();
            _edges_forward.resize(n_node);
            for (const auto& edge : raw_edges)
                _edges_forward[edge.from].push_back(edge.to);

            _edges_backward.clear();
            _edges_backward.resize(n_node);
            for (const auto& edge : raw_edges)
                _edges_backward[edge.to].push_back(edge.from);
        }
        size_t size() const { return raw_edges.size(); }

    public:
        void save(const std::filesystem::path& path)
        {
            sort();
            std::ofstream ofs(path, std::ios::binary);
            ofs.write(reinterpret_cast<const char*>(raw_edges.data()),
                      raw_edges.size() * sizeof(edge_t));
        }
        void load(const std::filesystem::path& path)
        {
            std::vector<edge_t> new_raw_edges;

            std::ifstream ifs(path, std::ios::binary);
            // Resize the vector.
            ifs.seekg(0, std::ios::end);
            new_raw_edges.resize(ifs.tellg() / sizeof(edge_t));
            ifs.seekg(0, std::ios::beg);
            // Read the data.
            ifs.read(reinterpret_cast<char*>(new_raw_edges.data()),
                     new_raw_edges.size() * sizeof(edge_t));
        }
    };
} // namespace graph
