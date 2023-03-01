#ifndef ARC_H
#define ARC_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define UNUSED(x) (void)x

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

/// 0xRRGGBBAA
#define GET_R(hex) (color >> 8 * 3 & 0xFF)
#define GET_G(hex) (color >> 8 * 2 & 0xFF)
#define GET_B(hex) (color >> 8 * 1 & 0xFF)
#define GET_A(hex) (color >> 8 * 0 & 0xFF)

void arch_createCanvasHeap(arch_Canvas* canvas, size_t width, size_t height)
{
    canvas->data   = (unsigned char*)malloc(sizeof(unsigned char) * width * height * arch_COLOR_NUM);
    canvas->width  = width;
    canvas->height = height;
}

void arch_freeCanvas(arch_Canvas* canvas) { free(canvas->data); }

void arch_line(arch_Canvas* canvas, size_t x0, size_t y0, size_t x1, size_t y1)
{
    UNUSED(canvas);
    UNUSED(x0);
    UNUSED(y0);
    UNUSED(x1);
    UNUSED(y1);
    assert(false && "function not implemented yet");
}
void arch_circle(arch_Canvas* canvas, size_t x, size_t y, float radius)
{
    UNUSED(canvas);
    UNUSED(x);
    UNUSED(y);
    UNUSED(radius);
    assert(false && "function not implemented yet");
}
void arch_rectangle(arch_Canvas* canvas, const uint32_t color, size_t x0, size_t y0, size_t x1, size_t y1)
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
#if 0
            *(uint32_t*)&canvas->data[height * canvas->width * arch_COLOR_NUM + width ] = color;
#else
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_RED]   = GET_R(color);
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_GREEN] = GET_G(color);
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_BLUE]  = GET_B(color);
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_ALFA]  = GET_A(color);
#endif
        }
    }
}

void arch_fill(arch_Canvas* canvas, const uint32_t color)
{

    for (size_t height = 0; height < canvas->height; height++)
    {
        for (size_t width = 0; width < canvas->width * arch_COLOR_NUM; width += arch_COLOR_NUM)
        {
#if 0
            *(uint32_t*)&canvas->data[height * canvas->width * arch_COLOR_NUM + width ] = color;
#else
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_RED]   = GET_R(color);
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_GREEN] = GET_G(color);
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_BLUE]  = GET_B(color);
            canvas->data[height * canvas->width * arch_COLOR_NUM + width + arch_ALFA]  = GET_A(color);
#endif
        }
    }
}
#endif // ARC_H