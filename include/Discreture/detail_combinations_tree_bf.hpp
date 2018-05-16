#pragma once

#include <vector>

namespace dscr
{
namespace detail
{
    using std::vector;
    template <class combination, class Func, class IntType>
    void combination_tree_helper0(Func f, IntType n)
    {
        UNUSED(n);
        combination x;
        f(x);
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper1(Func f, IntType n)
    {
        combination x(1);
        for (x[0] = 0; x[0] < n; ++x[0])
        {
            f(x);
        }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper2(Func f, IntType n)
    {
        combination x(2);
        for (x[0] = 0; x[0] + 1 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 0 < n; ++x[1])
            {
                f(x);
            }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper3(Func f, IntType n)
    {
        combination x(3);
        for (x[0] = 0; x[0] + 2 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 1 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 0 < n; ++x[2])
                {
                    f(x);
                }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper4(Func f, IntType n)
    {
        combination x(4);
        for (x[0] = 0; x[0] + 3 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 2 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 1 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 0 < n; ++x[3])
                    {
                        f(x);
                    }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper5(Func f, IntType n)
    {
        combination x(5);
        for (x[0] = 0; x[0] + 4 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 3 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 2 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 1 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 0 < n; ++x[4])
                        {
                            f(x);
                        }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper6(Func f, IntType n)
    {
        combination x(6);
        for (x[0] = 0; x[0] + 5 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 4 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 3 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 2 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 1 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 0 < n; ++x[5])
                            {
                                f(x);
                            }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper7(Func f, IntType n)
    {
        combination x(7);
        for (x[0] = 0; x[0] + 6 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 5 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 4 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 3 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 2 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 1 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 0 < n; ++x[6])
                                {
                                    f(x);
                                }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper8(Func f, IntType n)
    {
        combination x(8);
        for (x[0] = 0; x[0] + 7 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 6 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 5 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 4 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 3 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 2 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 1 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 0 < n; ++x[7])
                                    {
                                        f(x);
                                    }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper9(Func f, IntType n)
    {
        combination x(9);
        for (x[0] = 0; x[0] + 8 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 7 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 6 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 5 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 4 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 3 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 2 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 1 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 0 < n;
                                             ++x[8])
                                        {
                                            f(x);
                                        }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper10(Func f, IntType n)
    {
        combination x(10);
        for (x[0] = 0; x[0] + 9 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 8 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 7 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 6 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 5 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 4 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 3 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 2 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 1 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 0 < n;
                                                 ++x[9])
                                            {
                                                f(x);
                                            }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper11(Func f, IntType n)
    {
        combination x(11);
        for (x[0] = 0; x[0] + 10 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 9 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 8 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 7 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 6 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 5 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 4 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 3 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 2 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 1 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 0 < n;
                                                     ++x[10])
                                                {
                                                    f(x);
                                                }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper12(Func f, IntType n)
    {
        combination x(12);
        for (x[0] = 0; x[0] + 11 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 10 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 9 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 8 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 7 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 6 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 5 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 4 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 3 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 2 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 1 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 0 < n;
                                                         ++x[11])
                                                    {
                                                        f(x);
                                                    }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper13(Func f, IntType n)
    {
        combination x(13);
        for (x[0] = 0; x[0] + 12 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 11 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 10 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 9 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 8 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 7 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 6 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 5 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 4 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 3 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 2 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 1 < n;
                                                         ++x[11])
                                                        for (x[12] = x[11] + 1;
                                                             x[12] + 0 < n;
                                                             ++x[12])
                                                        {
                                                            f(x);
                                                        }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper14(Func f, IntType n)
    {
        combination x(14);
        for (x[0] = 0; x[0] + 13 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 12 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 11 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 10 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 9 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 8 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 7 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 6 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 5 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 4 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 3 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 2 < n;
                                                         ++x[11])
                                                        for (x[12] = x[11] + 1;
                                                             x[12] + 1 < n;
                                                             ++x[12])
                                                            for (x[13] =
                                                                   x[12] + 1;
                                                                 x[13] + 0 < n;
                                                                 ++x[13])
                                                            {
                                                                f(x);
                                                            }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper15(Func f, IntType n)
    {
        combination x(15);
        for (x[0] = 0; x[0] + 14 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 13 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 12 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 11 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 10 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 9 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 8 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 7 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 6 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 5 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 4 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 3 < n;
                                                         ++x[11])
                                                        for (x[12] = x[11] + 1;
                                                             x[12] + 2 < n;
                                                             ++x[12])
                                                            for (x[13] =
                                                                   x[12] + 1;
                                                                 x[13] + 1 < n;
                                                                 ++x[13])
                                                                for (x[14] =
                                                                       x[13] +
                                                                       1;
                                                                     x[14] + 0 <
                                                                     n;
                                                                     ++x[14])
                                                                {
                                                                    f(x);
                                                                }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper16(Func f, IntType n)
    {
        combination x(16);
        for (x[0] = 0; x[0] + 15 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 14 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 13 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 12 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 11 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 10 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 9 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 8 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 7 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 6 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 5 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 4 < n;
                                                         ++x[11])
                                                        for (x[12] = x[11] + 1;
                                                             x[12] + 3 < n;
                                                             ++x[12])
                                                            for (x[13] =
                                                                   x[12] + 1;
                                                                 x[13] + 2 < n;
                                                                 ++x[13])
                                                                for (x[14] =
                                                                       x[13] +
                                                                       1;
                                                                     x[14] + 1 <
                                                                     n;
                                                                     ++x[14])
                                                                    for (
                                                                      x[15] =
                                                                        x[14] +
                                                                        1;
                                                                      x[15] +
                                                                        0 <
                                                                      n;
                                                                      ++x[15])
                                                                    {
                                                                        f(x);
                                                                    }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper17(Func f, IntType n)
    {
        combination x(17);
        for (x[0] = 0; x[0] + 16 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 15 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 14 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 13 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 12 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 11 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 10 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 9 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 8 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 7 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 6 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 5 < n;
                                                         ++x[11])
                                                        for (x[12] = x[11] + 1;
                                                             x[12] + 4 < n;
                                                             ++x[12])
                                                            for (x[13] =
                                                                   x[12] + 1;
                                                                 x[13] + 3 < n;
                                                                 ++x[13])
                                                                for (x[14] =
                                                                       x[13] +
                                                                       1;
                                                                     x[14] + 2 <
                                                                     n;
                                                                     ++x[14])
                                                                    for (
                                                                      x[15] =
                                                                        x[14] +
                                                                        1;
                                                                      x[15] +
                                                                        1 <
                                                                      n;
                                                                      ++x[15])
                                                                        for (
                                                                          x[16] =
                                                                            x[15] +
                                                                            1;
                                                                          x[16] <
                                                                          n;
                                                                          ++x
                                                                            [16])
                                                                        {
                                                                            f(x);
                                                                        }
    }

    template <class combination, class Func, class IntType>
    void combination_tree_helper18(Func f, IntType n)
    {
        combination x(18);
        for (x[0] = 0; x[0] + 17 < n; ++x[0])
            for (x[1] = x[0] + 1; x[1] + 16 < n; ++x[1])
                for (x[2] = x[1] + 1; x[2] + 15 < n; ++x[2])
                    for (x[3] = x[2] + 1; x[3] + 14 < n; ++x[3])
                        for (x[4] = x[3] + 1; x[4] + 13 < n; ++x[4])
                            for (x[5] = x[4] + 1; x[5] + 12 < n; ++x[5])
                                for (x[6] = x[5] + 1; x[6] + 11 < n; ++x[6])
                                    for (x[7] = x[6] + 1; x[7] + 10 < n; ++x[7])
                                        for (x[8] = x[7] + 1; x[8] + 9 < n;
                                             ++x[8])
                                            for (x[9] = x[8] + 1; x[9] + 8 < n;
                                                 ++x[9])
                                                for (x[10] = x[9] + 1;
                                                     x[10] + 7 < n;
                                                     ++x[10])
                                                    for (x[11] = x[10] + 1;
                                                         x[11] + 6 < n;
                                                         ++x[11])
                                                        for (x[12] = x[11] + 1;
                                                             x[12] + 5 < n;
                                                             ++x[12])
                                                            for (x[13] =
                                                                   x[12] + 1;
                                                                 x[13] + 4 < n;
                                                                 ++x[13])
                                                                for (x[14] =
                                                                       x[13] +
                                                                       1;
                                                                     x[14] + 3 <
                                                                     n;
                                                                     ++x[14])
                                                                    for (
                                                                      x[15] =
                                                                        x[14] +
                                                                        1;
                                                                      x[15] +
                                                                        2 <
                                                                      n;
                                                                      ++x[15])
                                                                        for (
                                                                          x[16] =
                                                                            x[15] +
                                                                            1;
                                                                          x[16] +
                                                                            1 <
                                                                          n;
                                                                          ++x
                                                                            [16])
                                                                            for (
                                                                              x[17] =
                                                                                x[16] +
                                                                                1;
                                                                              x[17] <
                                                                              n;
                                                                              ++x
                                                                                [17])
                                                                            {
                                                                                f(x);
                                                                            }
    }
} // namespace detail
} // namespace dscr
