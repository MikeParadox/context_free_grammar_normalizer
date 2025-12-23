cmake_minimum_required(VERSION 4.0)

project(context_free_grammar_normalizer
        VERSION 0.1
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_EXTENSIONS False)

include_directories(includes)
enable_testing()

add_subdirectory(src)
#add_subdirectory(tests)

