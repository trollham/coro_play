#pragma once
#include <compare>
#include <coroutine>
#include <iterator>
#include <optional>

namespace coro_play
{
    template <typename T>
    struct generator
    {
        using value_type = T;
        struct promise_type
        {
            T current;
            generator<T> get_return_object() { return coro_handle::from_promise(*this); }
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always yield_value(T expr)
            {
                current = expr;
                return {};
            }
            void unhandled_exception() {}
            void return_void() {}
            std::suspend_never final_suspend() noexcept { return {}; }
        };
        using coro_handle = std::coroutine_handle<promise_type>;

        coro_handle handle;

        generator(coro_handle handle) : handle(handle) {}
        generator(generator const &) = delete;
        generator &operator=(generator const &) = delete;
        ~generator()
        {
            handle.destroy();
        }

        struct sentinel
        {
        };

        struct iterator
        {

            using iterator_category = std::input_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = value_type *;
            using reference = value_type &;

            coro_handle handle;
            
            reference operator*()
            {
                return handle.promise().current;
            }

            void operator++(int)
            {
                operator++();
            }

            iterator &operator++()
            {
                if (handle)
                {
                    handle.resume();
                }
                return *this;
            }

            friend bool operator==(generator::iterator const & lhs, generator::sentinel)
            {
                return !lhs.handle || lhs.handle.done();
            }
        };

        auto begin() const noexcept
        {
            handle.resume();
            return iterator(handle);
        }

        auto end() const noexcept
        {
            return sentinel();
        }
    };
}