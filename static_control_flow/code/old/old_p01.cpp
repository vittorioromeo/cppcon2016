// Copyright (c) 2016 Vittorio Romeo
// License: AFL 3.0 | https://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com



// The previous examples were taken from proposal P0128R0:
//
// open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0128r0.html
// {"constexpr if" - Ville Voutilainen}



// This paper was originally created as a "resurrection" of the very
// controversial previous "static if" N3322 and N3329 proposals:
//
// open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3322.pdf
// {"A Preliminary Proposal for a Static if" - Walter E. Brown}
//
// open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3329.pdf
// {"static if declaration" - W. Bright, H. Sutter, A. Alexandrescu}



// The above proposals were considered harmful in N3613, due to their
// unintuitive scope rules and inconsistency with the rest of the
// language:
//
// open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3613.pdf
// {"Static if considered" - B. Stroustrup, G. Dos Reis, A. Sutton}



// Starting with N4461 by V. Voutilainen, the idea of a compile-time
// `if` construct with familiar scope rules began to gain traction.
// Eventually, the proposed syntax and standard wording was revised
// multiple times in P0128R0, P0128R1, P0292R0, and P0292R1.
//

// The final revision, P0292R2, was accepted for C++17:
//
// http://open-std.org/JTC1/SC22/WG21/docs/papers/2016/p0292r2.html
// {"constexpr if: A slightly different syntax" - Jens Maurer}



// The code shown below is valid C++17:
/*
template <class T, class... Args>
unique_ptr<T> make_unique(Args&&... args)
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

// The proposed `constexpr if` has to follow these rules:
/*
    * Restricted to block scopes.

    * Always going to establish a new scope.

    * Required that there exists values of the condition so
      that either condition branch is well-formed.
*/

// The above rules deal with the controversial ideas of N3613, making
// `constexpr if` an intuitive and familiar compile-time version of
// the regular `if` statement.

// Here's an example of a more complex branch:
/*
    if constexpr (cond0)
        statement0;
    else if constexpr (cond1)
        statement1;
    else if constexpr (cond2)
        statement2;
    else
        statement3;
*/

// `if constexpr` is part of the C++17 standard...
// ...but you don't have to wait for your compiler to implement it!
// It turns out that we can create an equivalent construct with C++14
// language features, with, unfortunately, a slightly less enticing
// syntax.

// Let's see how in the next code segment.

int main()
{
}