
#ifndef ONLY_LIST_TESTS

#define TEST_CASE(name, ...)                                                                                                                         \
    static int test_##name()                                                                                                                         \
    {                                                                                                                                                \
        __VA_ARGS__                                                                                                                                  \
        SUCCESS("test " #name);                                                                                                                      \
        return 0;                                                                                                                                    \
    }

#include "fast_tests.h"

#define ARCH_IMPLEMENTATION
#include "../arc.h"

#define HEIGHT 64
#define WIDTH 64
#endif // ifndef ONLY_LIST_TESTS

TEST_CASE(circle, {
    unsigned char data[HEIGHT * WIDTH * arch_COLOR_NUM];
    arch_Canvas canvas = {.data = data, .width = WIDTH, .height = HEIGHT};
    UNUSED(canvas);

    TEST_EQ_CHAR(12, 12, "error");
})

TEST_CASE(read_write, {
    unsigned char data[WIDTH * HEIGHT * arch_COLOR_NUM];
    unsigned char data2[WIDTH * HEIGHT * arch_COLOR_NUM];
    arch_Canvas canvas  = {.data = data, .height = HEIGHT, .width = WIDTH};
    arch_Canvas canvas2 = {.data = data2, .height = HEIGHT, .width = WIDTH};

    if (writeBinaryImage("test.bin", &canvas) == 1)
    {
        FAIL("write file failed");
        return 1;
    }
    if (readBinaryImage("test.bin", &canvas2) == 1)
    {
        FAIL("read file failed");
        return 1;
    }

    for (size_t i = 0; i < WIDTH * HEIGHT * arch_COLOR_NUM; i++)
    {
        TEST_EQ_UCHAR(canvas2.data[i], canvas.data[i], "colors wont match up");
    }
})

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
#include __FILE__
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
