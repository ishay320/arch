#define TEST_PATH "test.c"

#ifndef ONLY_LIST_TESTS

#define TEST_CASE(name, ...)                                                                                                                         \
    static int test_##name()                                                                                                                         \
    {                                                                                                                                                \
        __VA_ARGS__                                                                                                                                  \
        SUCCESS("test " #name);                                                                                                                      \
        return 0;                                                                                                                                    \
    }
#endif // ifndef ONLY_LIST_TESTS

#include TEST_PATH

#undef TEST_CASE

#ifndef ONLY_LIST_TESTS
struct function_pair
{
    int (*fun)();
    const char* name;
};

int main(void)
{
    struct function_pair tests[] = {
#define ONLY_LIST_TESTS
#define TEST_CASE(name, ...) {test_##name, #name},
#include TEST_PATH
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int i;

    for (i = 0; i < num_tests; ++i)
    {
        /* stuff before test */
        if ((tests[i].fun)() == 1)
        {
            FAIL_V("test %s failed", tests[i].name);
        }
        /* stuff after test */
    }

    return 0;
}
#endif // ifndef ONLY_LIST_TESTS
