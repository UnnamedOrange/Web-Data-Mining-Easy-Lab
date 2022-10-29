#pragma once

#include <cctype>
#include <fstream>
#include <optional>
#include <vector>

#include "page_t.hpp"

namespace parser
{
    class page_parser final
    {
    private:
        std::ifstream ifs;
        enum class state_t
        {
            _unused,
            head_line,
            id,
            url,
            title,
            title_ex,
            title_ex_out,
            body,
            body_out,
            standby,
        } state;

    public:
        page_parser() {}

    public:
        template <typename path_t>
        void open(const path_t& path)
        {
            ifs.open(path);
            state = state_t::head_line;
        }

    public:
        std::optional<page_t> next()
        {
            if (ifs.eof())
                return std::nullopt;

            page_t page;
            bool page_loaded = false;

            std::string text;
            char ch{};

            while (ifs.get(ch))
            {
                switch (state)
                {
                case state_t::head_line:
                {
                    if (ch == '\n')
                        state = state_t::id;
                    break;
                }
                case state_t::id:
                {
                    if (ch == '\t')
                    {
                        page.id = std::stoi(text);
                        text.clear();
                        state = state_t::url;
                    }
                    else
                        text.push_back(ch);
                    break;
                }
                case state_t::url:
                {
                    if (ch == '\t')
                    {
                        page.url = text;
                        text.clear();
                        state = state_t::title;
                    }
                    else
                        text.push_back(ch);
                    break;
                }
                case state_t::title:
                {
                    if (ch == '\"')
                    {
                        if (text.empty())
                            state = state_t::title_ex;
                        else
                        {
                            text.pop_back();
                            page.title = text;
                            text.clear();
                            state = state_t::body;
                        }
                    }
                    else
                        text.push_back(ch);
                    break;
                }
                case state_t::title_ex:
                {
                    if (ch == '\"')
                        state = state_t::title_ex_out;
                    else
                        text.push_back(ch);
                    break;
                }
                case state_t::title_ex_out:
                {
                    if (ch == '\"')
                    {
                        text.push_back('\"');
                        state = state_t::title_ex;
                    }
                    else
                        state = state_t::title;
                    break;
                }
                case state_t::body:
                {
                    if (ch == '\"')
                        state = state_t::body_out;
                    else
                        text.push_back(ch);
                    break;
                }
                case state_t::body_out:
                {
                    if (ch == '\"')
                    {
                        text.push_back('\"');
                        state = state_t::body;
                    }
                    else
                    {
                        page.body = text;
                        text.clear();
                        state = state_t::standby;
                        page_loaded = true;
                    }
                    break;
                }
                case state_t::standby:
                {
                    if (std::isdigit(ch))
                    {
                        ifs.unget();
                        state = state_t::id;
                    }
                    break;
                }
                }
                if (page_loaded)
                    break;
            }

            if (page_loaded)
                return page;
            else
                return std::nullopt;
        }
    };
} // namespace parser
