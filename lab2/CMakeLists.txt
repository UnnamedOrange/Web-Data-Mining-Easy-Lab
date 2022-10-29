cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
    cluster
    VERSION 0.0.0
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
