#pragma once

#include <string>

struct page_t
{
    int id;
    std::string url;
    std::string title;
    std::string body;

    void clear() { *this = {}; }
};
