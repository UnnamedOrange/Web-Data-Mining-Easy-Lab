#pragma once

#include <cstdio>
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <string>

namespace parser
{
    class index_parser final
    {
    private:
        FILE* file{};

    public:
        ~index_parser() { try_close(); }

    private:
        void try_close() noexcept
        {
            if (file)
            {
                fclose(file);
                file = nullptr;
            }
        }

    public:
        void open(const std::string& path)
        {
            FILE* file_to_open = std::fopen(path.c_str(), "r");
            if (!file_to_open)
                throw std::runtime_error("Failed to open file: " + path);
            try_close();
            file = file_to_open;
        }

    public:
        std::optional<std::string> next()
        {
            if (std::feof(file))
                return std::nullopt;

            int unused;
            if (2 != std::fscanf(file, "%d:%d:", &unused, &unused))
                return std::nullopt;

            char buffer[128];
            if (nullptr == std::fgets(buffer, sizeof(buffer), file))
                throw std::runtime_error("Fail to read line.");

            return std::string(buffer, buffer + strlen(buffer) - 1);
        }
    };
} // namespace parser
