/*

   Color representation is uint32_t: 0xAABBGGRR

   Usage:
   #define ARCH_IMPLEMENTATION
   #include "arc.h"
   ...

 */
#ifndef ARCH_INCLUDE_H
#define ARCH_INCLUDE_H

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) (void)x
#define POW(x) (x) * (x)
typedef int err;

#ifndef ARCH_DEF
#ifdef ARCH_STATIC
#define ARCH_DEF static
#else
#define ARCH_DEF extern
#endif
#endif

typedef struct
{
    uint32_t* data;
    size_t width;
    size_t height;
} arch_Canvas;

enum
{
    arch_RED = 0,
    arch_GREEN,
    arch_BLUE,
    arch_ALFA,
    arch_COLOR_NUM,
};

// 0xAABBGGRR
#define ARCH_WHITE 0xFFFFFFFF
#define ARCH_BLACK 0xFF000000
#define ARCH_RED 0xFF0000FF
#define ARCH_RED 0xFF0000FF
#define ARCH_GREEN 0xFF00FF00
#define ARCH_BLUE 0xFFFF0000

#if 0
typedef union
{
    struct
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    unsigned char at[4];
    uint32_t hax;
} arch_Color;
#endif

#define GET_R(hex) (color >> 8 * 3 & 0xFF)
#define GET_G(hex) (color >> 8 * 2 & 0xFF)
#define GET_B(hex) (color >> 8 * 1 & 0xFF)
#define GET_A(hex) (color >> 8 * 0 & 0xFF)

ARCH_DEF void arch_createCanvasHeap(arch_Canvas* canvas, size_t width, size_t height);
ARCH_DEF void arch_freeCanvas(arch_Canvas* canvas);
ARCH_DEF void arch_line(arch_Canvas* canvas, size_t x0, size_t y0, size_t x1, size_t y1);
ARCH_DEF void arch_fillPixel(arch_Canvas* canvas, uint32_t color, size_t h, size_t w);
ARCH_DEF void arch_circle(arch_Canvas* canvas, uint32_t color, size_t x, size_t y, float radius);
ARCH_DEF void arch_rectangle(arch_Canvas* canvas, uint32_t color, size_t x0, size_t y0, size_t x1,
                             size_t y1);
ARCH_DEF void arch_fill(arch_Canvas* canvas, const uint32_t color);

ARCH_DEF err writeBinaryImage(const char* path, const arch_Canvas* canvas);
ARCH_DEF err readBinaryImage(const char* path, arch_Canvas* canvas);

#endif // ARCH_INCLUDE_H

#ifdef ARCH_IMPLEMENTATION

ARCH_DEF void arch_createCanvasHeap(arch_Canvas* canvas, size_t width, size_t height)
{
    canvas->data   = (uint32_t*)malloc(sizeof(uint32_t) * width * height);
    canvas->width  = width;
    canvas->height = height;
}

ARCH_DEF void arch_freeCanvas(arch_Canvas* canvas) { free(canvas->data); }

ARCH_DEF void arch_line(arch_Canvas* canvas, size_t x0, size_t y0, size_t x1, size_t y1)
{
    UNUSED(canvas);
    UNUSED(x0);
    UNUSED(y0);
    UNUSED(x1);
    UNUSED(y1);
    assert(false && "function not implemented yet");
}

ARCH_DEF void arch_fillPixel(arch_Canvas* canvas, uint32_t color, size_t h, size_t w)
{
    canvas->data[h * canvas->width + w] = color;
}

ARCH_DEF void arch_circle(arch_Canvas* canvas, uint32_t color, size_t x, size_t y, float radius)
{

    const size_t start_h = y - radius;
    const size_t start_w = x - radius;
    const size_t end_h   = y + radius;
    const size_t end_w   = x + radius;

    for (size_t height = start_h; height < end_h; height++)
    {
        for (size_t width = start_w; width < end_w * arch_COLOR_NUM; width++)
        {
            if (POW(x - height) + POW(y - width) > POW(radius))
            {
                continue;
            }

            arch_fillPixel(canvas, color, height, width);
        }
    }
}

ARCH_DEF void arch_rectangle(arch_Canvas* canvas, uint32_t color, size_t x0, size_t y0, size_t x1,
                             size_t y1)
{
    for (size_t height = 0; height < canvas->height; height++)
    {
        if (height < y0 || y1 <= height)
        {
            continue;
        }

        for (size_t width = 0; width < canvas->width; width++)
        {
            if (width < x0 || x1 <= width)
            {
                continue;
            }

            arch_fillPixel(canvas, color, height, width);
        }
    }
}

ARCH_DEF void arch_fill(arch_Canvas* canvas, const uint32_t color)
{

    for (size_t height = 0; height < canvas->height; height++)
    {
        for (size_t width = 0; width < canvas->width; width++)
        {
            arch_fillPixel(canvas, color, height, width);
        }
    }
}

ARCH_DEF err arch_writeBinaryImage(const char* path, const arch_Canvas* canvas)
{
    FILE* fp = fopen(path, "wb");
    if (!fp)
    {
        perror("ERROR: fopen");
        return EXIT_FAILURE;
    }
    size_t write = fwrite(canvas->data, 1, canvas->height * canvas->height * sizeof(size_t), fp);
    if (write != canvas->height * canvas->height * sizeof(size_t))
    {
        perror("ERROR: fwrite");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

ARCH_DEF err arch_readBinaryImage(const char* path, arch_Canvas* canvas)
{
    FILE* fp = fopen(path, "r");
    if (!fp)
    {
        perror("ERROR: fopen");
        return EXIT_FAILURE;
    }

    const size_t len = canvas->height * canvas->height * sizeof(size_t);
    size_t num       = fread(canvas->data, 1, len, fp);
    if (num != len)
    {
        printf("ERROR: fraed read %ld instead of %ld: %s\n", num, len, strerror(errno));
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
#endif // ARCH_IMPLEMENTATION

// TODO: Implement function that receive x,y and width, height and returns safe zone
