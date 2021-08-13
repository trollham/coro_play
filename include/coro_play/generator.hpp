#pragma once
#include <coroutine>

namespace coro_play
{
    template <typename T>
    struct generator
    {
        struct promise_type
        {
            T state;
            generator<T> get_return_object() { return coro_handle::from_promise(*this); }
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always yield_value(T expr)
            {
                state = expr;
                return {};
            }
            void unhandled_exception() {}
            void return_void() {}
            std::suspend_never final_suspend() noexcept { return {}; }
        };
        using coro_handle = std::coroutine_handle<promise_type>;

        coro_handle handle;

        operator T &()
        {
            return handle.promise().state;
        }

        generator(coro_handle const handle_) : handle(handle_) {}
        ~generator() {
            handle.destroy();
        }

        generator& get_next() {
            handle.resume();
            return *this;
        }
    };
}