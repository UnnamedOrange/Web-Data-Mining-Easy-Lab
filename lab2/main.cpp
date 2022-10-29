#include <iostream>

#include <flow/1_load_pages.hpp>
#include <flow/2_sample_pages.hpp>
#include <global.hpp>

#define WORKING_DIR_FOR_DEBUG R"(D:\Libraries\Downloads)"

int main(int argn, char** argv)
{
    if (argn > 1)
        global::working_dir = argv[1];
    else
    {
#ifndef WORKING_DIR_FOR_DEBUG
        std::cout << "No working directory specified. Input one: " << std::endl;
        std::string dir;
        std::getline(std::cin, dir);
        global::working_dir = dir;
#else
        global::working_dir = WORKING_DIR_FOR_DEBUG;
#endif
    }
    std::cout << "Use " << global::working_dir << " as working directory."
              << std::endl;

    bool success = false;
    do
    {
        if (!flow::load_pages())
            break;
        if (!flow::sample_pages())
            break;
        success = true;
    } while (0);
    if (!success)
        return 1;
}
