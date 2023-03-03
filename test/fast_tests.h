#include <stdio.h>

#define SUCCESS(prompt) printf("\033[32m[V]\033[0m %s\n", prompt)

#define FAIL(prompt) printf("\033[31m[X] %s:%d\033[0m\n\t" prompt "\n", __FILE__, __LINE__)
#define FAIL_V(prompt, ...) printf("\033[31m[X] %s:%d\033[0m\n\t" prompt "\n", __FILE__, __LINE__, __VA_ARGS__)

#define __FAIL_EXPLAIN_INT(prompt, first, second)                                                                                                    \
    printf("\033[31m[X] %s:%d\n\t%d is not equals to %d\033[0m : %s\n", __FILE__, __LINE__, first, second, prompt)

#define __FAIL_EXPLAIN_CHAR(prompt, first, second)                                                                                                   \
    printf("\033[31m[X] %s:%d\n\t%c is not equals to %c\033[0m : %s\n", __FILE__, __LINE__, first, second, prompt)

#define __FAIL_EXPLAIN_UCHAR(prompt, first, second)                                                                                                  \
    printf("\033[31m[X] %s:%d\n\t0x%X is not equals to 0x%X\033[0m : %s\n", __FILE__, __LINE__, first, second, prompt)

#define __FAIL_EXPLAIN_FLOAT(prompt, first, second)                                                                                                  \
    printf("\033[31m[X] %s:%d\n\t%f is not equals to %f\033[0m : %s\n", __FILE__, __LINE__, first, second, prompt)

#define TEST(equals, prompt)                                                                                                                         \
    do                                                                                                                                               \
    {                                                                                                                                                \
        if (!(equals))                                                                                                                               \
        {                                                                                                                                            \
            FAIL(prompt);                                                                                                                            \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)

#define TEST_EQ_INT(a, b, prompt)                                                                                                                    \
    do                                                                                                                                               \
    {                                                                                                                                                \
        const int first  = a;                                                                                                                        \
        const int second = b;                                                                                                                        \
        if (!(first == second))                                                                                                                      \
        {                                                                                                                                            \
            __FAIL_EXPLAIN_INT(prompt, first, second);                                                                                               \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)

#define TEST_EQ_CHAR(a, b, prompt)                                                                                                                   \
    do                                                                                                                                               \
    {                                                                                                                                                \
        const char first  = a;                                                                                                                       \
        const char second = b;                                                                                                                       \
        if (!(first == second))                                                                                                                      \
        {                                                                                                                                            \
            __FAIL_EXPLAIN_CHAR(prompt, first, second);                                                                                              \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)

#define TEST_EQ_UCHAR(a, b, prompt)                                                                                                                  \
    do                                                                                                                                               \
    {                                                                                                                                                \
        const unsigned char first  = a;                                                                                                              \
        const unsigned char second = b;                                                                                                              \
        if (!(first == second))                                                                                                                      \
        {                                                                                                                                            \
            __FAIL_EXPLAIN_UCHAR(prompt, first, second);                                                                                             \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)

#define TEST_EQ_FLOAT(a, b, prompt)                                                                                                                  \
    do                                                                                                                                               \
    {                                                                                                                                                \
        const float first  = a;                                                                                                                      \
        const float second = b;                                                                                                                      \
        if (!(first == second))                                                                                                                      \
        {                                                                                                                                            \
            __FAIL_EXPLAIN_FLOAT(prompt, first, second);                                                                                             \
            return 1;                                                                                                                                \
        }                                                                                                                                            \
    } while (0)

// TODO: macro that you pass int float... and it creates the macro automatically for TEST_EQ
// TODO: implement function that test speed
// TODO: Implement function that compare file to array bit by bit
