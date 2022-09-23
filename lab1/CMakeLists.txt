cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
    pagerank
    VERSION 0.0.0
    LANGUAGES C CXX
)

if(WIN32)
    execute_process(
        COMMAND "win_flex" "--wincompat" "--outfile=${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c"
                "${CMAKE_CURRENT_SOURCE_DIR}/parser/content.lex" COMMAND_ERROR_IS_FATAL ANY
    )
endif()

add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE main.cpp "${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c")
