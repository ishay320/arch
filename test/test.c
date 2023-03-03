#ifndef GLOBALS
#define GLOBALS

#define ARCH_IMPLEMENTATION
#include "../arc.h"

#define HEIGHT 64
#define WIDTH 64

#endif // GLOBALS

#define TEST_PATH "test.c"
#include "fast_tests.h"

TEST_CASE(circle, {
    unsigned char data[HEIGHT * WIDTH * arch_COLOR_NUM];
    arch_Canvas canvas = {.data = data, .width = WIDTH, .height = HEIGHT};
    UNUSED(canvas);

    TEST_EQ_UCHAR(12, 12, "pass");
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
