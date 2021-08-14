#include <coro_play/generator.hpp>
#include <concepts>
#include <ranges>
#include <gtest/gtest.h>

template <typename T>
requires std::integral<T> || std::floating_point<T>
    coro_play::generator<T> iota(T initial = {})
{
    auto current = initial;
    while (true)
        co_yield current++;
}
template <std::ranges::range R>
auto to_vector(R &&r)
{
    std::vector<std::ranges::range_value_t<R>> v;

    // if we can get a size, reserve that much
    if constexpr (requires { std::ranges::size(r); })
    {
        v.reserve(std::ranges::size(r));
    }

    // push all the elements
    for (auto &&e : r)
    {
        v.push_back(static_cast<decltype(e) &&>(e));
    }

    return v;
}

TEST(coroutines_test, generator_from_0)
{
    {
        std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto generator = iota<int>();
        std::vector<int> actual;
        for (auto && i : generator | std::ranges::views::take(10)) {
            actual.emplace_back(i);
        }
        ASSERT_EQ(actual, expected);
    }

    {
        std::vector<double> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto generator = iota<double>();
        std::vector<double> actual;
        for (auto && i : generator | std::ranges::views::take(10)) {
            actual.emplace_back(i);
        }
        ASSERT_EQ(actual, expected);
    }
}

TEST(coroutines_test, int_generator_from_1)
{
    {
        std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto generator = iota<int>(1);
        std::vector<int> actual;
        for (auto && i : generator | std::ranges::views::take(10)) {
            actual.emplace_back(i);
        }
        ASSERT_EQ(actual, expected);
    }

    {
        std::vector<double> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto generator = iota<double>(1);
        std::vector<double> actual;
        for (auto && i : generator | std::ranges::views::take(10)) {
            actual.emplace_back(i);
        }
        ASSERT_EQ(actual, expected);
    }
}
