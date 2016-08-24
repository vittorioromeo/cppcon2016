// Copyright (c) 2016 Vittorio Romeo
// License: AFL 3.0 | https://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com



#include <iostream>
#include "./impl/static_if.hpp"

// Here's `static_if` in action:

// clang-format off

struct banana   { void eat() { /* ... */ } };
struct peanuts  { void eat() { /* ... */ } };
struct water    { void drink() { /* ... */ } };
struct juice    { void drink() { /* ... */ } };

template <typename T> constexpr bool is_solid{false};
template <>           constexpr bool is_solid<banana>{true};
template <>           constexpr bool is_solid<peanuts>{true};

template <typename T> constexpr bool is_liquid{false};
template <>           constexpr bool is_liquid<water>{true};
template <>           constexpr bool is_liquid<juice>{true};

// clang-format on

template <typename T>
auto consume(T&& x)
{
    static_if(bool_v<is_solid<T>>)
        .then([](auto&& y)
            {
                y.eat();
                std::cout << "eating solid\n";
            })
        .else_if(bool_v<is_liquid<T>>)
        .then([](auto&& y)
            {
                y.drink();
                std::cout << "drinking liquid\n";
            })
        .else_([](auto&&)
            {
                std::cout << "cannot consume\n";
            })(FWD(x));
}

int main()
{
    consume(banana{});
    consume(water{});
    consume(peanuts{});
    consume(juice{});
    consume(int{});
    consume(float{});
}