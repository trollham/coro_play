find_package(GTest CONFIG REQUIRED)
include (GoogleTest)

add_executable(coro_test test.cpp)

gtest_discover_tests(coro_test)

target_link_libraries(coro_test PUBLIC GTest::gtest GTest::gtest_main coro_play)