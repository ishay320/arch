#include "fast_tests.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../third_party/stb_image_write.h"

#define ARCH_IMPLEMENTATION
#include "../arc.h"

#include <stdio.h>

int main(void)
{
    int x = 0;
    TEST_EQ_INT(1, ++x, "fine");
    SUCCESS("all test ran successfully");

#define WIDTH 128
#define HEIGHT 128
    unsigned char data[WIDTH * HEIGHT * 4];
    arch_Canvas canvas = {.data = data, .height = HEIGHT, .width = WIDTH};
    // arch_createCanvasHeap(&canvas, 100, 100);
    arch_fill(&canvas, (uint32_t)0x00000000);

    arch_circle(&canvas, (uint32_t)0xFF0000FF, canvas.width / 2, canvas.height / 2, 52);

    // arch_rectangle(&canvas, (uint32_t)0xFF0000FF, 20, 10, 90, 50);
    stbi_write_png("test.png", canvas.width, canvas.height, arch_COLOR_NUM, canvas.data, 0);
    // arch_freeCanvas(&canvas);

    return 0;
}
