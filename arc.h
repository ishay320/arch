#ifndef ARC_H
#define ARC_H
/*

   Color representation is 0xRRGGBBAA

   Usage:
   #define ARCH_IMPLEMENTATION
   #include "arc.h"
   ...

 */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define UNUSED(x) (void)x
#define POW(x) (x) * (x)
#define ARCH_DEFINE_FUN

typedef struct
{
    unsigned char* data;
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

ARCH_DEFINE_FUN void arch_createCanvasHeap(arch_Canvas* canvas, size_t width, size_t height);
ARCH_DEFINE_FUN void arch_freeCanvas(arch_Canvas* canvas);
ARCH_DEFINE_FUN void arch_line(arch_Canvas* canvas, size_t x0, size_t y0, size_t x1, size_t y1);
ARCH_DEFINE_FUN void arch_fillPixel(arch_Canvas* canvas, uint32_t color, size_t h, size_t w);
ARCH_DEFINE_FUN void arch_circle(arch_Canvas* canvas, uint32_t color, size_t x, size_t y, float radius);
ARCH_DEFINE_FUN void arch_rectangle(arch_Canvas* canvas, uint32_t color, size_t x0, size_t y0, size_t x1, size_t y1);
ARCH_DEFINE_FUN void arch_fill(arch_Canvas* canvas, const uint32_t color);

#ifdef ARCH_IMPLEMENTATION
ARCH_DEFINE_FUN void arch_createCanvasHeap(arch_Canvas* canvas, size_t width, size_t height)
{
    canvas->data   = (unsigned char*)malloc(sizeof(unsigned char) * width * height * arch_COLOR_NUM);
    canvas->width  = width;
    canvas->height = height;
}

ARCH_DEFINE_FUN void arch_freeCanvas(arch_Canvas* canvas) { free(canvas->data); }

ARCH_DEFINE_FUN void arch_line(arch_Canvas* canvas, size_t x0, size_t y0, size_t x1, size_t y1)
{
    UNUSED(canvas);
    UNUSED(x0);
    UNUSED(y0);
    UNUSED(x1);
    UNUSED(y1);
    assert(false && "function not implemented yet");
}

ARCH_DEFINE_FUN void arch_fillPixel(arch_Canvas* canvas, uint32_t color, size_t h, size_t w)
{
#ifdef ARCH_TYPE_PUNNING
    *(uint32_t*)&canvas->data[height * canvas->width * arch_COLOR_NUM + width] = color;
#else
    canvas->data[h * canvas->width * arch_COLOR_NUM + w + arch_RED]   = GET_R(color);
    canvas->data[h * canvas->width * arch_COLOR_NUM + w + arch_GREEN] = GET_G(color);
    canvas->data[h * canvas->width * arch_COLOR_NUM + w + arch_BLUE]  = GET_B(color);
    canvas->data[h * canvas->width * arch_COLOR_NUM + w + arch_ALFA]  = GET_A(color);
#endif
}

ARCH_DEFINE_FUN void arch_circle(arch_Canvas* canvas, uint32_t color, size_t x, size_t y, float radius)
{

    const size_t start_h = y - radius;
    const size_t start_w = x - radius;
    const size_t end_h   = y + radius;
    const size_t end_w   = x + radius;

    for (size_t height = start_h; height < end_h; height++)
    {
        for (size_t width = start_w; width < end_w * arch_COLOR_NUM; width += arch_COLOR_NUM)
        {
            if (POW(x - height) + POW(y - width / 4) > POW(radius))
            {
                continue;
            }

            arch_fillPixel(canvas, color, height, width);
        }
    }
}

ARCH_DEFINE_FUN void arch_rectangle(arch_Canvas* canvas, uint32_t color, size_t x0, size_t y0, size_t x1, size_t y1)
{
    for (size_t height = 0; height < canvas->height; height++)
    {
        if (height < y0 || y1 <= height)
        {
            continue;
        }

        for (size_t width = 0; width < canvas->width * arch_COLOR_NUM; width += arch_COLOR_NUM)
        {
            if (width / 4 < x0 || x1 <= width / 4)
            {
                continue;
            }

            arch_fillPixel(canvas, color, height, width);
        }
    }
}

ARCH_DEFINE_FUN void arch_fill(arch_Canvas* canvas, const uint32_t color)
{

    for (size_t height = 0; height < canvas->height; height++)
    {
        for (size_t width = 0; width < canvas->width * arch_COLOR_NUM; width += arch_COLOR_NUM)
        {

            arch_fillPixel(canvas, color, height, width);
        }
    }
}

#endif // ARCH_IMPLEMENTATION
#endif // ARC_H

// TODO: Implement function that receive x,y and width, height and returns safe zone
