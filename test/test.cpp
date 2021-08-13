#include <coro_play/generator.hpp>
#include <gtest/gtest.h>

template <typename T>
coro_play::generator<T> iota() {
    auto current = T{};
    while(true)
        co_yield current++,0;
}

TEST(coroutines_test, generator_from_0) {
    std::vector<int> expected{0,1,2,3,4,5,6};
    std::vector<int> actual;
    auto generator = iota<int>();
    for (int i = 0; i < 7; i++)
    {
        actual.push_back(generator.get_next());
    }

    ASSERT_EQ(actual, expected);
}

TEST(coroutines_test, generator_from_0_double)
{
    std::vector<double> expected{0,1,2,3,4,5,6};
    std::vector<double> actual;
    auto generator = iota<double>();
    for (int i = 0; i < 7; i++)
    {
        actual.push_back(generator.get_next());
    }

    ASSERT_EQ(actual, expected);
}