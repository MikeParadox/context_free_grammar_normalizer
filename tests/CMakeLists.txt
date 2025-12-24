find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
        fruitless_removal_tests fruitless_removal_tests.cpp
)

add_executable(inaccessible_removal_tests inaccessible_removal_tests.cpp)

target_link_libraries(
        fruitless_removal_tests
        Grammar
        GTest::gtest_main
)

target_link_libraries(
        inaccessible_removal_tests
        Grammar
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(fruitless_removal_tests)
gtest_discover_tests(inaccessible_removal_tests)


