#include <iostream>
#include <string>

#include <flow/1_load_indices.hpp>
#include <flow/2_load_pages.hpp>
#include <flow/3_cache_graph.hpp>

#define WORKING_PATH_FOR_DEBUG R"(D:\Libraries\Downloads\data)"

int main(int argn, char** argv)
{
    if (argn > 1)
        global::working_path = argv[1];
    else
    {
#ifndef WORKING_PATH_FOR_DEBUG
        std::cout << "No working path specified. Input one: " << std::endl;
        std::string path;
        std::getline(std::cin, path);
        global::working_path = path;
#else
        global::working_path = WORKING_PATH_FOR_DEBUG;
#endif
    }
    std::cout << "Use " << global::working_path << " as working path."
              << std::endl;

    bool success = false;
    do
    {
        if constexpr (true)
        {
            if (!flow::load_indices())
                break;
            if (!flow::load_pages())
                break;
            if (!flow::cache_graph())
                break;
        }
        success = true;
    } while (0);
    if (!success)
        return 1;
}
