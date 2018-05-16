#pragma once

#include <vector>

namespace dscr
{
namespace detail
{
    using std::vector;
    template <class combination, class Func, class IntType>
    void combination_helper0(Func f, IntType n)
    {
        UNUSED(n);
        combination x;
        f(x);
    }

    template <class combination, class Func, class IntType>
    void combination_helper1(Func f, IntType n)
    {
        combination x(1);
        for (x[0] = 0; x[0] < n; ++x[0])
        {
            f(x);
        }
    }

    template <class combination, class Func, class IntType>
    void combination_helper2(Func f, IntType n)
    {
        combination x(2);
        for (x[1] = 1; x[1] < n; ++x[1])
            for (x[0] = 0; x[0] < x[1]; ++x[0])
            {
                f(x);
            }
    }

    template <class combination, class Func, class IntType>
    void combination_helper3(Func f, IntType n)
    {
        combination x(3);
        for (x[2] = 2; x[2] < n; ++x[2])
            for (x[1] = 1; x[1] < x[2]; ++x[1])
                for (x[0] = 0; x[0] < x[1]; ++x[0])
                {
                    f(x);
                }
    }

    template <class combination, class Func, class IntType>
    void combination_helper4(Func f, IntType n)
    {
        combination x(4);
        for (x[3] = 3; x[3] < n; ++x[3])
            for (x[2] = 2; x[2] < x[3]; ++x[2])
                for (x[1] = 1; x[1] < x[2]; ++x[1])
                    for (x[0] = 0; x[0] < x[1]; ++x[0])
                    {
                        f(x);
                    }
    }

    template <class combination, class Func, class IntType>
    void combination_helper5(Func f, IntType n)
    {
        combination x(5);
        for (x[4] = 4; x[4] < n; ++x[4])
            for (x[3] = 3; x[3] < x[4]; ++x[3])
                for (x[2] = 2; x[2] < x[3]; ++x[2])
                    for (x[1] = 1; x[1] < x[2]; ++x[1])
                        for (x[0] = 0; x[0] < x[1]; ++x[0])
                        {
                            f(x);
                        }
    }

    template <class combination, class Func, class IntType>
    void combination_helper6(Func f, IntType n)
    {
        combination x(6);
        for (x[5] = 5; x[5] < n; ++x[5])
            for (x[4] = 4; x[4] < x[5]; ++x[4])
                for (x[3] = 3; x[3] < x[4]; ++x[3])
                    for (x[2] = 2; x[2] < x[3]; ++x[2])
                        for (x[1] = 1; x[1] < x[2]; ++x[1])
                            for (x[0] = 0; x[0] < x[1]; ++x[0])
                            {
                                f(x);
                            }
    }

    template <class combination, class Func, class IntType>
    void combination_helper7(Func f, IntType n)
    {
        combination x(7);
        for (x[6] = 6; x[6] < n; ++x[6])
            for (x[5] = 5; x[5] < x[6]; ++x[5])
                for (x[4] = 4; x[4] < x[5]; ++x[4])
                    for (x[3] = 3; x[3] < x[4]; ++x[3])
                        for (x[2] = 2; x[2] < x[3]; ++x[2])
                            for (x[1] = 1; x[1] < x[2]; ++x[1])
                                for (x[0] = 0; x[0] < x[1]; ++x[0])
                                {
                                    f(x);
                                }
    }

    template <class combination, class Func, class IntType>
    void combination_helper8(Func f, IntType n)
    {
        combination x(8);
        for (x[7] = 7; x[7] < n; ++x[7])
            for (x[6] = 6; x[6] < x[7]; ++x[6])
                for (x[5] = 5; x[5] < x[6]; ++x[5])
                    for (x[4] = 4; x[4] < x[5]; ++x[4])
                        for (x[3] = 3; x[3] < x[4]; ++x[3])
                            for (x[2] = 2; x[2] < x[3]; ++x[2])
                                for (x[1] = 1; x[1] < x[2]; ++x[1])
                                    for (x[0] = 0; x[0] < x[1]; ++x[0])
                                    {
                                        f(x);
                                    }
    }

    template <class combination, class Func, class IntType>
    void combination_helper9(Func f, IntType n)
    {
        combination x(9);
        for (x[8] = 8; x[8] < n; ++x[8])
            for (x[7] = 7; x[7] < x[8]; ++x[7])
                for (x[6] = 6; x[6] < x[7]; ++x[6])
                    for (x[5] = 5; x[5] < x[6]; ++x[5])
                        for (x[4] = 4; x[4] < x[5]; ++x[4])
                            for (x[3] = 3; x[3] < x[4]; ++x[3])
                                for (x[2] = 2; x[2] < x[3]; ++x[2])
                                    for (x[1] = 1; x[1] < x[2]; ++x[1])
                                        for (x[0] = 0; x[0] < x[1]; ++x[0])
                                        {
                                            f(x);
                                        }
    }

    template <class combination, class Func, class IntType>
    void combination_helper10(Func f, IntType n)
    {
        combination x(10);
        for (x[9] = 9; x[9] < n; ++x[9])
            for (x[8] = 8; x[8] < x[9]; ++x[8])
                for (x[7] = 7; x[7] < x[8]; ++x[7])
                    for (x[6] = 6; x[6] < x[7]; ++x[6])
                        for (x[5] = 5; x[5] < x[6]; ++x[5])
                            for (x[4] = 4; x[4] < x[5]; ++x[4])
                                for (x[3] = 3; x[3] < x[4]; ++x[3])
                                    for (x[2] = 2; x[2] < x[3]; ++x[2])
                                        for (x[1] = 1; x[1] < x[2]; ++x[1])
                                            for (x[0] = 0; x[0] < x[1]; ++x[0])
                                            {
                                                f(x);
                                            }
    }

    template <class combination, class Func, class IntType>
    void combination_helper11(Func f, IntType n)
    {
        combination x(11);
        for (x[10] = 10; x[10] < n; ++x[10])
            for (x[9] = 9; x[9] < x[10]; ++x[9])
                for (x[8] = 8; x[8] < x[9]; ++x[8])
                    for (x[7] = 7; x[7] < x[8]; ++x[7])
                        for (x[6] = 6; x[6] < x[7]; ++x[6])
                            for (x[5] = 5; x[5] < x[6]; ++x[5])
                                for (x[4] = 4; x[4] < x[5]; ++x[4])
                                    for (x[3] = 3; x[3] < x[4]; ++x[3])
                                        for (x[2] = 2; x[2] < x[3]; ++x[2])
                                            for (x[1] = 1; x[1] < x[2]; ++x[1])
                                                for (x[0] = 0; x[0] < x[1];
                                                     ++x[0])
                                                {
                                                    f(x);
                                                }
    }

    template <class combination, class Func, class IntType>
    void combination_helper12(Func f, IntType n)
    {
        combination x(12);
        for (x[11] = 11; x[11] < n; ++x[11])
            for (x[10] = 10; x[10] < x[11]; ++x[10])
                for (x[9] = 9; x[9] < x[10]; ++x[9])
                    for (x[8] = 8; x[8] < x[9]; ++x[8])
                        for (x[7] = 7; x[7] < x[8]; ++x[7])
                            for (x[6] = 6; x[6] < x[7]; ++x[6])
                                for (x[5] = 5; x[5] < x[6]; ++x[5])
                                    for (x[4] = 4; x[4] < x[5]; ++x[4])
                                        for (x[3] = 3; x[3] < x[4]; ++x[3])
                                            for (x[2] = 2; x[2] < x[3]; ++x[2])
                                                for (x[1] = 1; x[1] < x[2];
                                                     ++x[1])
                                                    for (x[0] = 0; x[0] < x[1];
                                                         ++x[0])
                                                    {
                                                        f(x);
                                                    }
    }

    template <class combination, class Func, class IntType>
    void combination_helper13(Func f, IntType n)
    {
        combination x(13);
        for (x[12] = 12; x[12] < n; ++x[12])
            for (x[11] = 11; x[11] < x[12]; ++x[11])
                for (x[10] = 10; x[10] < x[11]; ++x[10])
                    for (x[9] = 9; x[9] < x[10]; ++x[9])
                        for (x[8] = 8; x[8] < x[9]; ++x[8])
                            for (x[7] = 7; x[7] < x[8]; ++x[7])
                                for (x[6] = 6; x[6] < x[7]; ++x[6])
                                    for (x[5] = 5; x[5] < x[6]; ++x[5])
                                        for (x[4] = 4; x[4] < x[5]; ++x[4])
                                            for (x[3] = 3; x[3] < x[4]; ++x[3])
                                                for (x[2] = 2; x[2] < x[3];
                                                     ++x[2])
                                                    for (x[1] = 1; x[1] < x[2];
                                                         ++x[1])
                                                        for (x[0] = 0;
                                                             x[0] < x[1];
                                                             ++x[0])
                                                        {
                                                            f(x);
                                                        }
    }

    template <class combination, class Func, class IntType>
    void combination_helper14(Func f, IntType n)
    {
        combination x(14);
        for (x[13] = 13; x[13] < n; ++x[13])
            for (x[12] = 12; x[12] < x[13]; ++x[12])
                for (x[11] = 11; x[11] < x[12]; ++x[11])
                    for (x[10] = 10; x[10] < x[11]; ++x[10])
                        for (x[9] = 9; x[9] < x[10]; ++x[9])
                            for (x[8] = 8; x[8] < x[9]; ++x[8])
                                for (x[7] = 7; x[7] < x[8]; ++x[7])
                                    for (x[6] = 6; x[6] < x[7]; ++x[6])
                                        for (x[5] = 5; x[5] < x[6]; ++x[5])
                                            for (x[4] = 4; x[4] < x[5]; ++x[4])
                                                for (x[3] = 3; x[3] < x[4];
                                                     ++x[3])
                                                    for (x[2] = 2; x[2] < x[3];
                                                         ++x[2])
                                                        for (x[1] = 1;
                                                             x[1] < x[2];
                                                             ++x[1])
                                                            for (x[0] = 0;
                                                                 x[0] < x[1];
                                                                 ++x[0])
                                                            {
                                                                f(x);
                                                            }
    }

    template <class combination, class Func, class IntType>
    void combination_helper15(Func f, IntType n)
    {
        combination x(15);
        for (x[14] = 14; x[14] < n; ++x[14])
            for (x[13] = 13; x[13] < x[14]; ++x[13])
                for (x[12] = 12; x[12] < x[13]; ++x[12])
                    for (x[11] = 11; x[11] < x[12]; ++x[11])
                        for (x[10] = 10; x[10] < x[11]; ++x[10])
                            for (x[9] = 9; x[9] < x[10]; ++x[9])
                                for (x[8] = 8; x[8] < x[9]; ++x[8])
                                    for (x[7] = 7; x[7] < x[8]; ++x[7])
                                        for (x[6] = 6; x[6] < x[7]; ++x[6])
                                            for (x[5] = 5; x[5] < x[6]; ++x[5])
                                                for (x[4] = 4; x[4] < x[5];
                                                     ++x[4])
                                                    for (x[3] = 3; x[3] < x[4];
                                                         ++x[3])
                                                        for (x[2] = 2;
                                                             x[2] < x[3];
                                                             ++x[2])
                                                            for (x[1] = 1;
                                                                 x[1] < x[2];
                                                                 ++x[1])
                                                                for (x[0] = 0;
                                                                     x[0] <
                                                                     x[1];
                                                                     ++x[0])
                                                                {
                                                                    f(x);
                                                                }
    }

    template <class combination, class Func, class IntType>
    void combination_helper16(Func f, IntType n)
    {
        combination x(16);
        for (x[15] = 15; x[15] < n; ++x[15])
            for (x[14] = 14; x[14] < x[15]; ++x[14])
                for (x[13] = 13; x[13] < x[14]; ++x[13])
                    for (x[12] = 12; x[12] < x[13]; ++x[12])
                        for (x[11] = 11; x[11] < x[12]; ++x[11])
                            for (x[10] = 10; x[10] < x[11]; ++x[10])
                                for (x[9] = 9; x[9] < x[10]; ++x[9])
                                    for (x[8] = 8; x[8] < x[9]; ++x[8])
                                        for (x[7] = 7; x[7] < x[8]; ++x[7])
                                            for (x[6] = 6; x[6] < x[7]; ++x[6])
                                                for (x[5] = 5; x[5] < x[6];
                                                     ++x[5])
                                                    for (x[4] = 4; x[4] < x[5];
                                                         ++x[4])
                                                        for (x[3] = 3;
                                                             x[3] < x[4];
                                                             ++x[3])
                                                            for (x[2] = 2;
                                                                 x[2] < x[3];
                                                                 ++x[2])
                                                                for (x[1] = 1;
                                                                     x[1] <
                                                                     x[2];
                                                                     ++x[1])
                                                                    for (x[0] =
                                                                           0;
                                                                         x[0] <
                                                                         x[1];
                                                                         ++x[0])
                                                                    {
                                                                        f(x);
                                                                    }
    }

    template <class combination, class Func, class IntType>
    void combination_helper17(Func f, IntType n)
    {
        combination x(17);
        for (x[16] = 16; x[16] < n; ++x[16])
            for (x[15] = 15; x[15] < x[16]; ++x[15])
                for (x[14] = 14; x[14] < x[15]; ++x[14])
                    for (x[13] = 13; x[13] < x[14]; ++x[13])
                        for (x[12] = 12; x[12] < x[13]; ++x[12])
                            for (x[11] = 11; x[11] < x[12]; ++x[11])
                                for (x[10] = 10; x[10] < x[11]; ++x[10])
                                    for (x[9] = 9; x[9] < x[10]; ++x[9])
                                        for (x[8] = 8; x[8] < x[9]; ++x[8])
                                            for (x[7] = 7; x[7] < x[8]; ++x[7])
                                                for (x[6] = 6; x[6] < x[7];
                                                     ++x[6])
                                                    for (x[5] = 5; x[5] < x[6];
                                                         ++x[5])
                                                        for (x[4] = 4;
                                                             x[4] < x[5];
                                                             ++x[4])
                                                            for (x[3] = 3;
                                                                 x[3] < x[4];
                                                                 ++x[3])
                                                                for (x[2] = 2;
                                                                     x[2] <
                                                                     x[3];
                                                                     ++x[2])
                                                                    for (x[1] =
                                                                           1;
                                                                         x[1] <
                                                                         x[2];
                                                                         ++x[1])
                                                                        for (
                                                                          x[0] =
                                                                            0;
                                                                          x[0] <
                                                                          x[1];
                                                                          ++x
                                                                            [0])
                                                                        {
                                                                            f(x);
                                                                        }
    }

    template <class combination, class Func, class IntType>
    void combination_helper18(Func f, IntType n)
    {
        combination x(18);
        for (x[17] = 17; x[17] < n; ++x[17])
            for (x[16] = 16; x[16] < x[17]; ++x[16])
                for (x[15] = 15; x[15] < x[16]; ++x[15])
                    for (x[14] = 14; x[14] < x[15]; ++x[14])
                        for (x[13] = 13; x[13] < x[14]; ++x[13])
                            for (x[12] = 12; x[12] < x[13]; ++x[12])
                                for (x[11] = 11; x[11] < x[12]; ++x[11])
                                    for (x[10] = 10; x[10] < x[11]; ++x[10])
                                        for (x[9] = 9; x[9] < x[10]; ++x[9])
                                            for (x[8] = 8; x[8] < x[9]; ++x[8])
                                                for (x[7] = 7; x[7] < x[8];
                                                     ++x[7])
                                                    for (x[6] = 6; x[6] < x[7];
                                                         ++x[6])
                                                        for (x[5] = 5;
                                                             x[5] < x[6];
                                                             ++x[5])
                                                            for (x[4] = 4;
                                                                 x[4] < x[5];
                                                                 ++x[4])
                                                                for (x[3] = 3;
                                                                     x[3] <
                                                                     x[4];
                                                                     ++x[3])
                                                                    for (x[2] =
                                                                           2;
                                                                         x[2] <
                                                                         x[3];
                                                                         ++x[2])
                                                                        for (
                                                                          x[1] =
                                                                            1;
                                                                          x[1] <
                                                                          x[2];
                                                                          ++x
                                                                            [1])
                                                                            for (
                                                                              x[0] =
                                                                                0;
                                                                              x[0] <
                                                                              x[1];
                                                                              ++x
                                                                                [0])
                                                                            {
                                                                                f(x);
                                                                            }
    }

    template <class combination, class Func, class IntType>
    void combination_helper19(Func f, IntType n)
    {
        combination x(19);
        for (x[18] = 18; x[18] < n; ++x[18])
            for (x[17] = 17; x[17] < x[18]; ++x[17])
                for (x[16] = 16; x[16] < x[17]; ++x[16])
                    for (x[15] = 15; x[15] < x[16]; ++x[15])
                        for (x[14] = 14; x[14] < x[15]; ++x[14])
                            for (x[13] = 13; x[13] < x[14]; ++x[13])
                                for (x[12] = 12; x[12] < x[13]; ++x[12])
                                    for (x[11] = 11; x[11] < x[12]; ++x[11])
                                        for (x[10] = 10; x[10] < x[11]; ++x[10])
                                            for (x[9] = 9; x[9] < x[10]; ++x[9])
                                                for (x[8] = 8; x[8] < x[9];
                                                     ++x[8])
                                                    for (x[7] = 7; x[7] < x[8];
                                                         ++x[7])
                                                        for (x[6] = 6;
                                                             x[6] < x[7];
                                                             ++x[6])
                                                            for (x[5] = 5;
                                                                 x[5] < x[6];
                                                                 ++x[5])
                                                                for (x[4] = 4;
                                                                     x[4] <
                                                                     x[5];
                                                                     ++x[4])
                                                                    for (x[3] =
                                                                           3;
                                                                         x[3] <
                                                                         x[4];
                                                                         ++x[3])
                                                                        for (
                                                                          x[2] =
                                                                            2;
                                                                          x[2] <
                                                                          x[3];
                                                                          ++x
                                                                            [2])
                                                                            for (
                                                                              x[1] =
                                                                                1;
                                                                              x[1] <
                                                                              x[2];
                                                                              ++x
                                                                                [1])
                                                                                for (
                                                                                  x[0] =
                                                                                    0;
                                                                                  x[0] <
                                                                                  x[1];
                                                                                  ++x
                                                                                    [0])
                                                                                {
                                                                                    f(x);
                                                                                }
    }

} // namespace detail
} // namespace dscr
