// Copyright (c) 2016 Vittorio Romeo
// License: AFL 3.0 | https://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com



// +-----------------------------------------------+
// |                                               |
// |  Implementing `static` control flow in C++14  |
// |                  CppCon 2016                  |
// |                                               |
// |    https://github.com/SuperV1234/cppcon2016   |
// |                                               |
// +-----------------------------------------------+

// Talk overview (TODO):
/*
    p00:    * What is "static" control flow?

    p01:    * History of "static if" in C++.
            * C++17: `if constexpr`.

    p02:    * `static_if` example.

    p03:    * `static_if` implementation.

    p04:    * Additional `static_if` examples.
*/

// Talk overview:
/*
    * Branching at compile-time.
        * "static" branching overview.
        * `if constexpr` overview.
        * `static_if` implementation and examples.

    * Iteration at compile-time.
        * `for_each_argument`: explanation and limitations.
        * `static_for` example and overview.
        * `static_for` implementation.

    * Brief overhead analysis.
    * Available production-ready solutions.
*/

// `static` is a specifier with multiple meanings in C++.

// It is also a word very commonly used by developers to refer to
// compile-time control flow.

// "static if" is a name given to the compile-time counterpart of the
// `if` statement - its inclusion in the C++ language has been
// controversially proposed multiple times, but it has found a home
// in other languages. (C++17 will finally introduce a compile-time 
// branching construct that we're going to analyze in this talk.)

// C++ developers often feel that the functional purity of template
// metaprogramming and its lack of explicit control flow options make
// compile-time code harder to implement and to reason about.

// In this talk, we'll analyze and implement two powerful compile-time
// C++14 control flow constructs: `static_if` and `static_for`.

// Before doing that, we'll look at some examples of `static if` in 
// action in other languages, and at the new `if constexpr` construct.

// An example of a language with `static if` is "D":

/*
template INT(int i)
{
    static if (i == 32)
        alias INT = int;
    else static if (i == 16)
        alias INT = short;
    else
        static assert(0); // not supported
}
*/

// The above D code snippet shows a working compile-time `static if`,
// where every branch does not introduce a new scope.

// To achieve the same result in C++, a solution based on "explicit
// template specialization" can be used:

/*
template<int i>
struct INT;

template<>
struct INT<32>
{
    using type = int;
};

template<>
struct INT<16>
{
    using type = short;
};
*/

// "static if" is not only useful when defining type aliases, but it's
// very convenient (and considered superior to specialization) in
// contexts where a small piece of code needs to be conditionally
// executed depending on a compile-time condition.

// Here's an example, regarding variadic argument packs:

/*
// Traditional solution: two overloads.

template <class T>
void f(T&& t)
{
    // handle one T
}
template <class T, class... Rest>
void f(T&& t, Rest&&... r)
{
    f(t);
    // handle the tail
    f(r...);
}

// With "static if": one overload.
template <class T, class... Rest>
void f(T&& t, Rest&&... r)
{
    f(t);

    static_if (sizeof...(r))
    {
        // handle the tail
        f(r...);
    }
}
*/

// Here's an additional example, regarding object construction with
// the `(...)` syntax versus the `{...}` syntax:

/*
// Traditional solution: explicit specialization + `enable_if`.
template <class T, class... Args>
enable_if_t<is_constructible_v<T, Args...>, unique_ptr<T>>
make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(forward<Args>(args)...));
}
template <class T, class... Args>
enable_if_t<!is_constructible_v<T, Args...>, unique_ptr<T>>
make_unique(Args&&... args)
{
    return unique_ptr<T>(new T{forward<Args>(args)...});
}

// With "static if": one function, that's much easier to read.
template <class T, class... Args>
auto make_unique(Args&&... args)
{
    if constexpr(is_constructible_v<T, Args...>)
    {
        return unique_ptr<T>(new T(forward<Args>(args)...));
    }
    else
    {
        return unique_ptr<T>(new T{forward<Args>(args)...});
    }
}
*/

// The above examples were not created by me: they are part of a
// series of proposals that led to the inclusion of `if constexpr` in
// the upcoming C++17 standard.

// Let's learn more about that in the next code segment.

int main()
{
}