#pragma once

#include <cstdio>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "FlexLexer.h"
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
        std::ifstream ifs;
        std::vector<char> iobuf;
        yyFlexLexer lexer;

    private:
        page_t current_page;

    public:
        void open(const std::string& path)
        {
            ifs.open(path);
            iobuf.resize(2 * 1024 * 1024);
            ifs.rdbuf()->pubsetbuf(iobuf.data(), iobuf.size());
            lexer.yyrestart(ifs);
        }

    public:
        std::optional<page_t> next()
        {
            page_t ret;

            token_t token;
            do
            {
                token = static_cast<token_t>(lexer.yylex());
                if (token > token_t::t_unused)
                {
                    switch (token)
                    {
                    case token_t::t_title:
                    {
                        current_page.title = lexer.YYText();
                        break;
                    }
                    case token_t::t_link:
                    {
                        current_page.links.push_back(
                            std::string(lexer.YYText() + 2,
                                        lexer.YYText() + lexer.YYLeng() - 2));
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
