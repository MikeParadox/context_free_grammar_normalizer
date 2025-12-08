add_library(Grammar)

target_sources(Grammar
        PRIVATE
        #        Grammar.cpp
        PUBLIC
        FILE_SET CXX_MODULES FILES
        Grammar.ixx
)

add_executable(main main.cpp)

target_compile_options(main PRIVATE
        -fopenmp -g -ggdb -Werror -Wall -pedantic
        -Wnull-dereference -Wextra -Wshadow -Wnon-virtual-dtor
        -finput-charset=UTF-8 -Weffc++)# enable UTF-8 support for GCC


target_link_libraries(main PRIVATE Grammar)

