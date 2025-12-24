find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
        grammar_tests fruitless_removal_tests.cpp
)

target_link_libraries(
        grammar_tests
        Grammar
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(grammar_tests)


