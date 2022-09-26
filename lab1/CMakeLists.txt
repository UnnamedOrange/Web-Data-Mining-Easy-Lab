cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(
    pagerank
    VERSION 0.0.0
    LANGUAGES C CXX
)

if(WIN32)
    execute_process(
        COMMAND
            "win_flex" "--wincompat" "--c++"
            "--outfile=${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/page.lex" COMMAND_ERROR_IS_FATAL ANY
    )
else()
    execute_process(
        COMMAND "flex" "--c++" "--outfile=${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/parser/page.lex" COMMAND_ERROR_IS_FATAL ANY
    )
endif()

add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/parser")
target_sources(${PROJECT_NAME} PRIVATE main.cpp "${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp")
target_sources(${PROJECT_NAME} PRIVATE "flow/1_load_indices.hpp" "flow/2_load_pages.hpp")
