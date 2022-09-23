#pragma once

#include <cstdio>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "lex_interface.h"

struct page_t
{
    std::string title;
    std::vector<std::string> links;
    void clear()
    {
        title.clear();
        links.clear();
    }
};

namespace parser
{
    class page_parser final
    {
    private:
        FILE*(&file) = yyin;
        char*(&buffer) = yytext;
        const int(&length) = yyleng;

    private:
        page_t current_page;

    public:
        ~page_parser() { try_close(); }

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
        std::optional<page_t> next()
        {
            page_t ret;

            token_t token;
            do
            {
                token = static_cast<token_t>(yylex());
                if (token > token_t::t_unused)
                {
                    switch (token)
                    {
                    case token_t::t_title:
                    {
                        current_page.title = buffer;
                        break;
                    }
                    case token_t::t_link:
                    {
                        current_page.links.push_back(
                            std::string(buffer + 2, buffer + length - 2));
                        break;
                    }
                    case token_t::t_page_begin:
                    {
                        current_page.clear();
                        break;
                    }
                    case token_t::t_page_end:
                    {
                        ret = std::move(current_page);
                        return ret;
                    }
                    default:
                        break;
                    }
                }
            } while (token != token_t::t_eof);
            return std::nullopt;
        }
    };
} // namespace parser
