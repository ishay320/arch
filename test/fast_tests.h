#include <iostream>

#define SUCCESS(prompt) std::cout << "\033[32m[V]\033[0m " << prompt << '\n'

#define FAIL(prompt) std::cout << "\033[31m[X] " << __FILE__ << ':' << __LINE__ << "\033[0m\n\t" << prompt << '\n'

#define TEST(equals, prompt)                                                                                                                         \
    do                                                                                                                                               \
    {                                                                                                                                                \
        if (!(equals))                                                                                                                               \
        {                                                                                                                                            \
            FAIL(prompt);                                                                                                                            \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)

#define TEST_EQ(a, b, prompt)                                                                                                                        \
    do                                                                                                                                               \
    {                                                                                                                                                \
        const auto first  = a;                                                                                                                       \
        const auto second = b;                                                                                                                       \
        if (!(first == second))                                                                                                                      \
        {                                                                                                                                            \
            FAIL("\033[31m" << first << " is not equals " << second << "\033[0m : " << prompt);                                                      \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)
