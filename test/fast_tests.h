/* Usage:
1.  you can create your own main and use the TEST_EQ etc.

2.  if you want TEST_CASES then your main test file will look like:
```
#ifndef GLOBALS
#define GLOBALS
    // defines and includes put here
#endif // GLOBALS

#define TEST_PATH "path to the file"
#include "fast_tests.h"

TEST_CASE(test_name, {
    // do tests
})

// more test cases
```
 */

#ifndef FAST_TESTS_H
#define FAST_TESTS_H

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

/*******************/
/* TEST_CASES part */
/*******************/

#define TEST_CASE(name, ...)                                                                                                                         \
    static int test_##name()                                                                                                                         \
    {                                                                                                                                                \
        __VA_ARGS__                                                                                                                                  \
        SUCCESS("test " #name);                                                                                                                      \
        return 0;                                                                                                                                    \
    }

// Test case functions definition
#ifdef TEST_PATH
#include TEST_PATH
#endif // TEST_PATH

struct ft_function_pair
{
    int (*fun)();
    const char* name;
};

#ifdef TEST_PATH
int main(void)
{
    // Tests functions array
    struct ft_function_pair tests[] = {
#define ONLY_LIST_TESTS
#undef TEST_CASE
#define TEST_CASE(name, ...) {test_##name, #name},
#include TEST_PATH
    };
    int num_tests                = sizeof(tests) / sizeof(tests[0]);
    static char* test_ok         = "OK";
    static char* test_ok_color   = "\033[32m";
    static char* test_fail       = "FAIL";
    static char* test_fail_color = "\033[31m";

    for (int i = 0; i < num_tests; ++i)
    {
        /* stuff before test */
        int err           = (tests[i].fun)();
        char* test_status = (err == 1) ? test_fail : test_ok;
        char* test_color  = (err == 1) ? test_fail_color : test_ok_color;
        printf("TEST %d/%d %s %s[%s]\033[0m\n", i + 1, num_tests, tests[i].name, test_color, test_status);
        /* stuff after test */
    }

    return 0;
}

#undef TEST_CASE
#define TEST_CASE(...)
#endif // TEST_PATH

#endif // FAST_TESTS_H

// TODO: macro that you pass int float... and it creates the macro automatically for TEST_EQ
// TODO: implement function that test speed
// TODO: Implement function that compare file to array bit by bit
// TODO: put the errors after the fail prompt